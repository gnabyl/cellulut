#include"database.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <iostream>

DBManager* DBManager::DBManInstance = nullptr;

DBManager::DBManager(const QString& path){
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
    bool test = query.prepare("SELECT * FROM Automata");
    query.exec();
    while(query.next()){
        QMessageBox* window = new QMessageBox;
        window->setText(query.value("name").toString());
        window->show();
    }
}

DBManager::~DBManager(){
    db.close();
}

void DBManager::DBaddNeighborhood(const QString& name, int nbNeighbors ,int* dx, int* dy ){
    QSqlQuery query;
    query.prepare("INSERT INTO Neighborhood (:name);");
    query.bindValue(":name", name);
       if(!query.exec()){
            qDebug() << "addNeighborhood error:"
                     << query.lastError().text();
       }
       int n = 0;
       while(n < nbNeighbors){
           QSqlQuery query;
           query.prepare("INSERT INTO Neighbor (:name, :dx,:dy);");
           query.bindValue(":name", name);
           query.bindValue(":dx", dx[n]);
           query.bindValue(":dy", dy[n]);
           if(!query.exec()){
                qDebug() << "addNeighbor error:"
                         << query.lastError().text();
           }
           n++;
       }
}

std::pair<std::pair< int*, int* >,int> DBManager::DBSelectNeighborhood(const QString& name){
    QSqlQuery query;
    query.prepare("SELECT dx,dy FROM Neighborhood JOIN Neighbor ON Neighborhood.name=Neighbor.name WHERE Neighborhood.name=(:name);");
    query.bindValue(":name", name);
    int * dx;
    int*dy;
    int i=0;
    while (query.next()) {
        dx[i]=query.value(0).toInt();
        dy[i]=query.value(1).toInt();
        i++;
    }
    return std::make_pair(std::make_pair(dx, dy),i);

};

