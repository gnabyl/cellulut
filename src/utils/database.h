#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include "automata_manager.h"

class DBException{
    std::string info;
public:
    DBException(const std::string& s) : info(s){}
    const std::string& getInfo() const{return info;}
};

class DBManager{
    DBManager(const QString&);
    QSqlDatabase db;
    DBManager(const DBManager*) = delete;
    DBManager operator=(const DBManager*) = delete;
    static DBManager* DBManInstance;

public:
    ~DBManager();
    static DBManager& getDB();
    static void closeDB();

    void loadAutomatasFromDB() const;
};

#endif // DATABASE_H
