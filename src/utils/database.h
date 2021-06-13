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

/**
 * @brief The DBException class gestionnaire d'erreurs
 */

class DBException{
    /**
     * @brief info message d'erreur
     */
    std::string info;
public:
    /**
     * @brief DBException constructeur de la classe DBException
     * @param s chaine de caractères concernant le message d'erreur
     */
    DBException(const std::string& s) : info(s){}
    /**
     * @brief getInfo récupère l'information (message d'erreur)
     * @return le message d'erreur
     */
    const std::string& getInfo() const{return info;}
};
/**
 * @brief The DBManager class gestionnaire de la BDD
 */
class DBManager{
    /**
     * @brief DBManager  Constructeur
     */
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
    void insertAutomataIntoDB(QString name,int nbStates, QString transitionName, QString neighborhoodName,CellState** chosenStates,QString description = "",QString author = "",int year = 0);
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
