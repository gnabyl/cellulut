#include <string>
#include <iostream>
#include "automata.h"
#include "transition-strategy.h"
#include "neighbor-strategy.h"
#include "cellstate.h"
#include "grid.h"
using namespace std;

Automata::Automata(CellState** c, ITransitionStrategy t,INeighborStrategy n,unsigned short nb, string na, string d,string a,unsigned short y)
{
    name=na;
    description=d;
    author=a;
    creationYear=y;
    nbStates=nb;
    availableStates=new CellState*[nbStates];
    for(int i=0;i<nbStates;i++)
    {
        availableStates[i]=c[i];
    }
    transitionStrategy=t;
    neighborStrategy=n;
}

Automata::~Automata()
{
    if(availableStates!= nullptr)
    {
        for(int i;i<nbStates;i++)
        {
            if(availableStates[i]!= nullptr)
            {
                delete availableStates[i];
                availableStates[i]= nullptr;
            }
        }
        delete[] availableStates;
        availableStates= nullptr;
    }
}

Grid& Automata::applyTransition(const Grid& src) const
{

}

void Automata::setAvailableStates(const CellStates** c, unsigned short taille)
{
    if(nbStates!=taille)
    {
        nbStates=taille;
        CellState** newTab = new CellState*[taille];
        for(size_t i = 0; i< taille; i++) newTab[i] = c[i];
        CellSTate** old = availableStates;
        availableStates = newTab;
        delete[] old;
    }
    for(size_t i;i<taille;i++) availableStates[i]=c[i];
}

void Automata::setAvailableState(const CellState* c,const unsigned short i)
{
    if(i>=nbStates) throw "Error: availableStates incorrect index";
    availableStates[i]=c;

}

CellState* Automata::getAvailableState(const unsigned short i) const
{
    if(i>=nbStates) throw "Error: availableStates incorrect index";
    return availableStates[i];
}