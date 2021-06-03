#include"database.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

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
        DBManInstance = new DBManager(QString::fromStdString("./DBB.db"));
    return *DBManInstance;
}

void DBManager::loadAutomatasFromDB() const{
    AutomataManager* automataManager = AutomataManager::getAutomataManager();
    QSqlQuery query;
    query.prepare("SELECT * FROM Automata");
    query.exec();
    //Et voilà, c'est la merde. query.exec() renvoie false, je ne sais pas pourquoi la commande ne veut pas s'exécuter...
}

DBManager::~DBManager(){
    db.close();
}
