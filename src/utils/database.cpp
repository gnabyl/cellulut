#include"database.h"
#include <QMessageBox>
#include <QSqlQuery>
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
