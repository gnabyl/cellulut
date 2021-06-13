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
#include "grid_factory.h"

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
    GridFactory gridFac;

public:
    ~DBManager();
    static DBManager& getDB();
    static void closeDB();

    void loadAutomatasFromDB() const;
    void insertAutomataIntoDB(QString name,int nbStates, QString transitionName, QString neighborhoodName,CellState** chosenStates);
    QColor toColor(const QString& col) const;

    void insertNeighborhoodIntoDB(const QString name, const int radius) const;
    void insertNeighborhoodIntoDB(const QString name, int nbNeighbors, const int* dx,const int *dy)const;
    std::pair<int, NeighborhoodStrategy**> loadNeighborhoodsFromDB() const;
    void loadStatesFromDB() const;
    std::pair<int,CellState**> loadStatesfromDB() const;
    std::pair<int, TransitionStrategy**>loadTransitionsFromDB() const;

    void insertConfigIntoDB(const QString& name, Grid* config, Automata* automata) const;
    std::pair<int, Grid**> loadConfigsFromDB(Automata* automata) const;
};


#endif // DATABASE_H
