#ifndef LO21_AUTOMATAMANAGER_H
#define LO21_AUTOMATAMANAGER_H
#include <iostream>
#include "automata.h"
#include "transition-strategy.h"
#include "neighbor-strategy.h"
#include "cellstate.h"
#include "grid.h"

#define MAX_AUTOMATA 1000

using namespace std;

class AutomataManager
{
private:
    static AutomataManager* instance; //Instance unique (singleton)
    static unsigned short nbAutomatas;
    static const unsigned short nbMaxAutomatas=MAX_AUTOMATA;
    Automata** automatas;

    AutomataManager(const AutomataManager& a)=delete;
    AutomataManager();
    ~AutomataManager();
    void operator=(const AutomataManager& a)=delete;

public:
    static AutomataManager& getAutomataManager();
    static void destroyAutomataManager();

    const Automata& getAutomata(unsigned short id) const;
    void changeAutomata(unsigned short id,CellState** c,ITransitionStrategy t,INeighborStrategy n,unsigned short nb=0,string na="", string d="",string a="",unsigned short y=2021);
    void addAutomata(CellState** c,ITransitionStrategy t,INeighborStrategy n,unsigned short nb=0,string na="", string d="",string a="",unsigned short y=2021);
    void removeAutomata(unsigned short id);

    unsigned short getNbAutomatas() const {return nbAutomatas;}
};

#endif //LO21_AUTOMATAMANAGER_H
