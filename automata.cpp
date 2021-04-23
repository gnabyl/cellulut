#include <string>
#include <iostream>
#include "automata.h"
//#include "transition-strategy.h"
//#include "neighbor-strategy.h"
//#include "cellState.h"
//#include "grid.h"
using namespace std;

Automata::Automata(CellState** c, ITransitionStrategy t,INeighborStrategy n,size_t nb, string na, string d,string a,size_t y)
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
    delete[] availableStates;
    availableStates= nullptr;
}

void Automata::applyTransition(const Grid& src, Grid& dest) const
{

}

void Automata::setAvailableStates(const CellStates** c, size_t taille)
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

void Automata::setAvailableState(const CellState* c,const size_t i)
{
    if(i>=nbStates) throw "Erreur indice availableStates incorrect";
    availableStates[i]=c;

}

CellState* Automata::getAvailableState(const size_t i) const
{
    if(i>=nbStates) throw "Erreur indice availableStates incorrect";
    return availableStates[i];
}