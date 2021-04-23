#ifndef LO21_AUTOMATAMANAGER_H
#define LO21_AUTOMATAMANAGER_H
#include <iostream>
#include "automata.h"
//#include "transition-strategy.h"
//#include "neighbor-strategy.h"
//#include "cellState.h"
//#include "grid.h"

using namespace std;

class AutomataManager
{
private:
    static AutomataManager* instance; //Instance unique (singleton)
    static size_t nbAutomatas;
    static const size_t nbMaxAutomatas=1000; // A DEFINIR : Limite de nb d'automate pour pouvoir instancier le tableau d'automate
    Automata** automatas;

    AutomataManager(const AutomataManager& a)=delete;
    AutomataManager();
    ~AutomataManager();
    void operator=(const AutomataManager& a)=delete;

public:
    static AutomataManager& getAutomataManager();
    static void destroyAutomataManager();

    const Automata& getAutomata(size_t id) const;
    void setAutomata(size_t id,CellState** c,ITransitionStrategy t,INeighborStrategy n,size_t nb=0,string na="", string d="",string a="",size_t y=2021);
    void removeAutomata(size_t id);

    size_t getNbAutomatas() const {return nbAutomatas;}
};

#endif //LO21_AUTOMATAMANAGER_H
