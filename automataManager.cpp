#include <iostream>
#include "automata.h"
#include "automataManager.h"
//#include "transition-strategy.h"
//#include "neighbor-strategy.h"
//#include "cellState.h"
//#include "grid.h"

AutomataManager* AutomataManager::instance=nullptr;

AutomataManager::AutomataManager()
{
    for(int i;i<nbMaxAutomatas;i++) automatas[i]= nullptr;
}

AutomataManager::~AutomataManager()
{
    for(int i;i<nbMaxAutomatas;i++) delete automatas[i];
}

AutomataManager& AutomataManager::getAutomataManager()
{
    if(!instance) instance=new AutomataManager();
    return *instance;
}

void AutomataManager::destroyAutomataManager()
{
    delete instance;
    instance= nullptr;
    nbAutomatas=0;
}

const Automata& AutomataManager::getAutomata(size_t id) const
{
    if(id>nbMaxAutomatas) throw "Indice d'automate incorrect!";
    if(automatas[id]== nullptr) throw "Erreur: Automate non défini";
    return *automatas[id];
}

void AutomataManager::setAutomata(size_t id,CellState** c, ITransitionStrategy t,INeighborStrategy n,size_t nb, string na, string d,string a,size_t y)
{
    if(id>nbMaxAutomatas) throw "Indice d'automate incorrect!";
    if(automatas[id]== nullptr) nbAutomatas++;
    automatas[id]=new Automata(c,t,n,nb,na,d,a,y);
}

void AutomataManager::removeAutomata(size_t id)
{
    if(id>nbMaxAutomatas) throw "Indice d'automate incorrect!";
    if(automatas[id]!= nullptr) nbAutomatas--;
    delete automatas[id];
    automatas[id]= nullptr;
}




