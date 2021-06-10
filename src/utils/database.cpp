#include"database.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <iostream>
#include"neighborhood_factory.h"

DBManager* DBManager::DBManInstance = nullptr;

DBManager::DBManager(const QString& path) {

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if(!db.open())
        throw DBException("Error : failed to access database !");
    else {
        QMessageBox window;
        window.setText("Connection with database correctly established !");
        window.exec();
    }
}

std::pair<int , CellState**> DBManager::loadStatefromDB() const{
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("SELECT COUNT(*) FROM State");
    query.exec();
    query.next();
    int nb=query.value(0).toInt();
    CellState** Statetab= new CellState*[nb];
    query.prepare("SELECT * FROM State");
    query.exec();
    int i =0;
    while(query.next()) {
        QString label,direction;
        QString col;
        QColor color;
        int id;
        label = query.value("label").toString();
        col = query.value("color").toString();
        direction = query.value("direction").toString();
        id=query.value("id").toInt();
        color= toColor(col);
        Statetab[i]=new CellState(id, label.toStdString(), color);
        i++;}
    return {nb,Statetab};
}

DBManager& DBManager::getDB() {
    if(DBManInstance == nullptr)
        DBManInstance = new DBManager(DB_PATH);
    return *DBManInstance;
}

void DBManager::loadAutomatasFromDB() const {
    AutomataManager* automataManager = AutomataManager::getAutomataManager();
    QSqlQuery query(this->db);
    query.prepare("SELECT * FROM Automata");
    query.exec();
    bool test3 = query.isActive();
    QSqlQuery queryAux(this->db);
    while(query.next()) {
        // Infos that are easy to take from DB :
        QString name, description, author;
        int nbStates, creationYear;

        name = query.value("name").toString();
        description = query.value("description").toString();
        author = query.value("author").toString();
        nbStates = query.value("nbStates").toInt();
        creationYear = query.value("creationYear").toInt();

        //Slightly more difficult infos :
        // Available states
        CellState** availableStates = new CellState*[nbStates];
        queryAux.prepare(QString("SELECT stateID FROM AutomataState WHERE automataName = :name"));
        queryAux.bindValue(":name", name);
        queryAux.exec();

        int i = 0;

        QSqlQuery queryAuxState(this->db);
        while(queryAux.next()) { //Take infos about the concerned states to dynamically create those objects
            int stateID = queryAux.value("stateID").toInt();
            queryAuxState.prepare(QString("SELECT * FROM State WHERE id = :stateID"));
            queryAuxState.bindValue(":stateID", stateID);
            queryAuxState.exec();
            queryAuxState.next();
            QString label = queryAuxState.value("label").toString();
            QString col = queryAuxState.value("color").toString();
            QColor color = toColor(col);
            //See how to handle direction

            availableStates[i] = new CellState(stateID, label.toStdString(), color);

            i++;
        }
        queryAux.finish();
        queryAuxState.finish();

        bool test = queryAux.isActive();
        bool test2 = queryAuxState.isActive();

        QString rule = query.value("transition").toString();
        QString neighborhood = query.value("neighborhood").toString();

        automataManager->addAutomata(availableStates,
                                     transitionFac.production(rule.toStdString()),
                                     neighborFac.production(neighborhood.toStdString()),
                                     nbStates, name.toStdString(), description.toStdString(),
                                     author.toStdString(), creationYear);

    }

    query.finish();
    test3 = query.isActive();
}

QColor DBManager::toColor(const QString& col) const {
    if(col == "black") return Qt::black;
    if(col == "white") return Qt::white;
    if(col == "yellow") return Qt::yellow;
    if(col == "blue") return Qt::blue;
    if(col == "cyan") return Qt::cyan;
    if(col == "darkcyan") return Qt::darkCyan;
    if(col == "red") return Qt::red;
    if(col == "green") return Qt::green;
    if(col == "magenta") return Qt::magenta;
    return Qt::white;
}

DBManager::~DBManager() {
    db.close();
}


void DBManager::DBaddNeighborhood(const QString name, const int radius) const {
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("INSERT INTO Neighborhood (:name,:radius)");
    query.bindValue(":name", name + QString::number(radius));
    query.bindValue(":radius", radius);
    if(!query.exec()) {
        qDebug() << "addNeighborhood error:"
                 << query.lastError().text();
    }
}

void DBManager::DBaddNeighborhood(const QString name, const int* dx, const int* dy) const {
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("INSERT INTO Neighborhood (:name)");
    query.bindValue(":name", name);
    if(!query.exec()) {
        qDebug() << "addNeighborhood error:"
                 << query.lastError().text();
    }
    int n = 0;
    while(dx[n]) {
        QSqlQuery query(QSqlDatabase::database());
        query.prepare("INSERT INTO Neighbor (:name, :dx,:dy)");
        query.bindValue(":name", name);
        query.bindValue(":dx", dx[n]);
        query.bindValue(":dy", dy[n]);
        if(!query.exec()) {
            qDebug() << "addNeighbor error:"
                     << query.lastError().text();
        }

        n++;
    }


}


std::pair<int, NeighborhoodStrategy**> DBManager::loadNeighborhoodFromDB() const {
    NeighborhoodFactory* e = new NeighborhoodFactory;
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("SELECT COUNT(*) FROM Neighborhood");
    query.exec();
    query.next();
    int n = query.value(0).toInt();
    NeighborhoodStrategy** res = new NeighborhoodStrategy*[n];
    NeighborhoodStrategy* neighborhood;
    query.finish();
    QSqlQuery queryAux(QSqlDatabase::database());
    queryAux.prepare("SELECT name, radius FROM Neighborhood");
    queryAux.exec();
    int i = 0;
    while(queryAux.next()) {
        QString name = queryAux.value(0).toString();
        int radius = queryAux.value(1).toInt();
        QSqlQuery query1(QSqlDatabase::database());
        query1.prepare("SELECT COUNT(dx) FROM Neighborhood JOIN Neighbor ON Neighborhood.name=Neighbor.name WHERE Neighborhood.name=(:name) GROUP BY dx;");
        query1.bindValue(":name", name);
        query1.exec();
        int nbNeighbors=query1.value(0).toInt();
        query1.prepare("SELECT dx,dy FROM Neighborhood JOIN Neighbor ON Neighborhood.name=Neighbor.name WHERE Neighborhood.name=(:name);");
        query1.bindValue(":name", name);
        query1.exec();
        std::string stringName = name.toStdString();
        if(query1.value(0).toInt() == 0) {
            if(query1.value(1).toInt() == 0) {
                neighborhood = e->production(name.toStdString());
            } else {
                neighborhood = e->production(name.toStdString(), radius);
            }
        } else {
            int* dx = new int[nbNeighbors];
            int* dy = new int[nbNeighbors];
            int j = 0;
            while (query1.next()) {
                dx[j] = query1.value(0).toInt();
                dy[j] = query1.value(1).toInt();
                j++;
            }
            neighborhood = e->production(name.toStdString(), nbNeighbors, dx, dy);
        }
        res[i] = neighborhood;
        i++;
    }
    delete e;
    query.finish();
    return {n, res};
}

std::pair<int, TransitionStrategy**> DBManager::loadTransitionsFromDB() const {
    TransitionFactory* e = new TransitionFactory;
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("SELECT COUNT(*) FROM Transition");
    query.exec();
    query.next();
    int n = query.value(0).toInt();
    TransitionStrategy** res = new TransitionStrategy*[n];
    TransitionStrategy* transition;
    query.finish();
    QSqlQuery queryAux(QSqlDatabase::database());
    queryAux.prepare("SELECT name FROM Transition");
    queryAux.exec();


    int i = 0;
    while(queryAux.next()) {
        QString name=queryAux.value(0).toString();
        std::string nameString=name.toStdString();
        transition = e->production(nameString);
        res[i] = transition;
        i++;
    }
    delete e;
    queryAux.finish();
    return {n, res};
}

