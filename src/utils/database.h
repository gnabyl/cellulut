#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

class DBException{
    std::string info;
public:
    DBException(const std::string& s) : info(s){}
    const std::string& getInfo() const{return info;}
};

class DBManager{
    QSqlDatabase db;

public:
    DBManager(const QString&);
};

#endif // DATABASE_H
