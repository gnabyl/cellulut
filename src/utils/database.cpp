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
    else{
        QMessageBox* window = new QMessageBox();
        window->setText("Connection with database correctly established !");
        window->show();
    }
}

DBManager& DBManager::getDB(){
    if(DBManInstance == nullptr)
        DBManInstance = new DBManager(DB_PATH);
    return *DBManInstance;
}

void DBManager::loadAutomatasFromDB() const{
    AutomataManager* automataManager = AutomataManager::getAutomataManager();
    QSqlQuery query(this->db);
    query.prepare("SELECT * FROM Automata");
    query.exec();
    while(query.next()){
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
        QSqlQuery queryAux(this->db);
        queryAux.prepare(QString("SELECT stateID FROM AutomataState WHERE automataName = :name"));
        queryAux.bindValue(":name",name);
        queryAux.exec();

        int i = 0;

        while(queryAux.next()){ //Take infos about the concerned states to dynamically create those objects
            int stateID = queryAux.value("stateID").toInt();
            QSqlQuery queryAuxState(this->db);
            queryAuxState.prepare(QString("SELECT * FROM CellState WHERE id = :stateID"));
            queryAuxState.bindValue(":stateID",stateID);
            queryAuxState.exec();

            while (queryAuxState.next()) {
                QString label = queryAuxState.value("label").toString();
                QString col = queryAuxState.value("color").toString();
                QColor color = toColor(col);
                //See how to handle direction

                availableStates[i] = new CellState(stateID, label.toStdString(), color);

                i++;
            }
        }

        QString rule = query.value("transition").toString();
        QString neighborhood = query.value("neighborhood").toString();

        automataManager->addAutomata(availableStates,transitionFac.production(rule.toStdString()),toNeighborhood(neighborhood),nbStates,name.toStdString(),description.toStdString(),author.toStdString(),creationYear);
    }
}

QColor DBManager::toColor(const QString& col) const{
    if(col == "black") return Qt::black;
    if(col == "white") return Qt::white;
    if(col == "yellow") return Qt::yellow;
    if(col == "blue") return Qt::blue;
}

NeighborhoodStrategy* DBManager::toNeighborhood(const QString &neighborhood) const{
    if(neighborhood == "Moore Neighborhood") return new MooreNeighborhood;
    if(neighborhood == "Von Neumann Neighborhood") return new VonNeumannNeighborhood;
    if(neighborhood == "Moore Neighborhood Generalized") return new MooreNeighborhoodGeneralized(1);
    if(neighborhood == "Von Neumann Neighborhood Generalized") return new MooreNeighborhoodGeneralized(1);
}

DBManager::~DBManager(){
    db.close();
}


void DBManager::DBaddNeighborhood(const QString name, const int radius) const{
        QSqlQuery query;
        query.prepare("INSERT INTO Neighborhood (:name,:radius);");
        query.bindValue(":name", name+QString::number(radius));
        query.bindValue(":radius",radius);
           if(!query.exec()){
                qDebug() << "addNeighborhood error:"
                         << query.lastError().text();
           }


}
void DBManager::DBaddNeighborhood(const QString name, const int* dx,const int *dy) const{
    QSqlQuery query;
    query.prepare("INSERT INTO Neighborhood (:name);");
    query.bindValue(":name", name);
       if(!query.exec()){
            qDebug() << "addNeighborhood error:"
                     << query.lastError().text();}
   int n = 0;
   while(dx[n]){
       QSqlQuery query;
       query.prepare("INSERT INTO Neighbor (:name, :dx,:dy);");
       query.bindValue(":name", name);
       query.bindValue(":dx", dx[n]);
       query.bindValue(":dy", dy[n]);
       if(!query.exec()){
            qDebug() << "addNeighbor error:"
                     << query.lastError().text();}

       n++;
   }


}


NeighborhoodStrategy** DBManager::loadNeighborhood() const{
    NeighborhoodFactory* e=new NeighborhoodFactory;
    QSqlQuery query;
    query.exec("SELECT count(name) FROM Neighborhood;");
    unsigned int n=query.value(0).toInt();
    NeighborhoodStrategy** res= new NeighborhoodStrategy*[n];
    NeighborhoodStrategy* neighborhood;
    query.exec("SELECT name, radius FROM Neighborhood;");
    int i=0;
    while(query.next()){
        QString name=query.value(0).toString();
        int radius=query.value(1).toInt();
        QSqlQuery query1;
        query1.exec("SELECT COUNT(dx) FROM Neighborhood JOIN Neighbor ON Neighborhood.name=Neighbor.name WHERE Neighborhood.name=(:name) GROUP BY dx;");
        int nbNeighbors=query1.value(0).toInt();
        query1.prepare("SELECT dx,dy FROM Neighborhood JOIN Neighbor ON Neighborhood.name=Neighbor.name WHERE Neighborhood.name=(:name);");
        query1.bindValue(":name", name);
        query1.exec();
        std::string stringName=name.toStdString();
        if(query1.value(0).isNull()){
            if(query1.value(1).isNull()){
                neighborhood=e->production(stringName);
            }
            else{neighborhood=e->production(stringName,radius);}
        }
        else{
            int *dx =new int[nbNeighbors];
            int*dy= new int[nbNeighbors];
            int j=0;
            while (query1.next()) {
                dx[j]=query1.value(0).toInt();
                dy[j]=query1.value(1).toInt();
                j++;
            }
            neighborhood=e->production(stringName,nbNeighbors,dx,dy);
        }
        res[i]=neighborhood;
        i++;
    }
    delete e;
    return res;
}

