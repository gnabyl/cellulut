#include <string>
#include <iostream>
#include "automata.h"
using namespace std;

Automata::Automata(CellState** c, TransitionStrategy* t, NeighborhoodStrategy* n, int nb, string na, string d, string a, int y) {
    name = na;
    description = d;
    author = a;
    creationYear = y;
    nbStates = nb;
    availableStates = new CellState*[nbStates];
    for(int i = 0; i < nbStates; i++) {
        availableStates[i] = c[i];
    }
    transitionStrategy = t;
    neighborStrategy = n;
}

Automata::~Automata() {
    if(availableStates != nullptr) {
        for(int i = 0; i < nbStates; i++) {
            if(availableStates[i] != nullptr) {
                delete availableStates[i];
                availableStates[i] = nullptr;
            }
        }
        delete[] availableStates;
        availableStates = nullptr;
    }
}

Grid& Automata::applyTransition(const Grid& src) const {
    Grid* dst = new Grid(availableStates[0], src.getWidth(), src.getHeight());
    for(int i = 0; i < src.getHeight(); i++) {
        for(int j = 0; j < src.getWidth(); j++) {
            //Pour chaque cellule on appele la méthode calcNextCell pour la modifier en fonction de son voisinage et de la fonction de transition
            dst->setCell(transitionStrategy->calcNextCell(src.getCell(i, j),
                                                          neighborStrategy->getNeighborhood()[i * dst->getWidth() + j],
                                                          neighborStrategy->getNbNeighbors(),
                                                          availableStates,
                                                          nbStates), i, j);
        }
    }
    return *dst;
}

void Automata::setAvailableStates(CellState** c, int taille) {
    if(nbStates != taille) {
        nbStates = taille;
        CellState** newTab = new CellState*[taille];
        for(int i = 0; i < taille; i++) newTab[i] = c[i];
        CellState** old = availableStates;
        availableStates = newTab;
        delete[] old;
    }
    for(int i = 0; i < taille; i++) availableStates[i] = c[i];
}

void Automata::setAvailableState(CellState* c, const int i) {
    if(i >= nbStates) throw "Error: availableStates incorrect index";
    availableStates[i] = c;

}

CellState* Automata::getAvailableState(const int i) const {
    if(i >= nbStates) throw "Error: availableStates incorrect index";
    return availableStates[i];
}
