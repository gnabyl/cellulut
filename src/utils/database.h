#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QColor>
#include <map>
#include "../constants.h"
#include "automata_manager.h"
#include "neighborhood_factory.h"
#include "transition_factory.h"

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
    TransitionFactory transitionFac;
    NeighborhoodFactory neighborFac;

public:
    ~DBManager();
    static DBManager& getDB();
    static void closeDB();

    void loadAutomatasFromDB() const;
    QColor toColor(const QString& col) const;

    void DBaddNeighborhood(const QString name, const int radius) const;
    void DBaddNeighborhood(const QString name, const int* dx,const int *dy)const;
    std::pair<int, NeighborhoodStrategy**> loadNeighborhoodFromDB() const;
    void loadStatesFromDB() const;
    void loadTransitionsFromDB();
    std::pair<int,CellState**> loadStatefromDB() const;
};


#endif // DATABASE_H
