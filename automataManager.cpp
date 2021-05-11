#include <iostream>
#include "automata.h"
#include "automataManager.h"
#include "transition-strategy.h"
#include "neighbor-strategy.h"
#include "cellstate.h"
#include "grid.h"
using namespace std;

AutomataManager* AutomataManager::instance=nullptr;

AutomataManager::AutomataManager()
{
    automatas=new Automata*[nbMaxAutomatas];
    for(int i;i<nbMaxAutomatas;i++) automatas[i]= nullptr;
    nbAutomatas=0;
}

AutomataManager::~AutomataManager()
{
    if(automatas!= nullptr)
    {
        for(int i;i<nbMaxAutomatas;i++)
        {
            if(automatas[i]!= nullptr)
            {
                delete automatas[i];
                automatas[i] = nullptr;
            }
        }
        delete[] automatas;
        automatas= nullptr;
    }
    nbAutomatas=0;
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
}

const Automata& AutomataManager::getAutomata(unsigned short id) const
{
    if(id>nbMaxAutomatas) throw "Error: Automaton incorrect index";
    if(automatas[id]== nullptr) throw "Error: Undefined automaton";
    return *automatas[id];
}

//Modification d'un automate à un indice donné
void AutomataManager::changeAutomata(unsigned short id,CellState** c, ITransitionStrategy t,INeighborStrategy n,unsigned short nb, string na, string d,string a,unsigned short y)
{
    if(id>=nbAutomatas) throw "Error: Automaton incorrect index";
    automatas[id]=new Automata(c,t,n,nb,na,d,a,y);
}

//Ajout d'un automate à la fin du tableau d'automates
void AutomataManager::addAutomata(CellState** c, ITransitionStrategy t,INeighborStrategy n,unsigned short nb, string na, string d,string a,unsigned short y)
{
    if(nbAutomatas>=nbMaxAutomatas) throw "Error : can't be added because the automaton table is full";
    automatas[nbAutomatas]=new Automata(c,t,n,nb,na,d,a,y);
    nbAutomatas++;
}

//Supression d'un automate à un indice donné, réajustement tableau pour éviter les trous
void AutomataManager::removeAutomata(unsigned short id=nbAutomatas-1)
{
    if(id>=nbAutomatas) throw "Error: Automaton incorrect index";
    //On décale les automates pour combler la supression
    while(id<nbAutomatas-1)
    {
        automatas[id]=automatas[id+1];
        id++;
    }
    delete automatas[id];
    automatas[id]= nullptr;
    nbAutomatas--;
}




