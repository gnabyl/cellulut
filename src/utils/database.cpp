#include"database.h"
#include <QMessageBox>

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

