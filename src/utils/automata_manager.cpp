#include <iostream>
#include "automata.h"
#include "automata_manager.h"

using namespace std;

AutomataManager* AutomataManager::instance = nullptr;

AutomataManager::AutomataManager() {
    automatas = new Automata*[nbMaxAutomatas];
    for(int i = 0; i < nbMaxAutomatas; i++) automatas[i] = nullptr;
    nbAutomatas = 0;
}

AutomataManager::~AutomataManager() {
    if(automatas != nullptr) {
        for(int i = 0; i < nbMaxAutomatas; i++) {
            if(automatas[i] != nullptr) {
                delete automatas[i];
                automatas[i] = nullptr;
            }
        }
        delete[] automatas;
        automatas = nullptr;
    }
    nbAutomatas = 0;
}

AutomataManager* AutomataManager::getAutomataManager() {
    if(!instance) instance = new AutomataManager();
    return instance;
}

void AutomataManager::destroyAutomataManager() {
    delete instance;
    instance = nullptr;
}
Automata* AutomataManager::getAutomata(int id) const {
    if(id > nbMaxAutomatas) throw "Error: Automaton incorrect index";
    if(automatas[id] == nullptr) throw "Error: Undefined automaton";
    return automatas[id];
}

//Modification d'un automate à un indice donné
void AutomataManager::changeAutomata(int id, CellState** c, TransitionStrategy* t, NeighborhoodStrategy* n, int nb, string na, string d, string a, int y) {
    if(id >= nbAutomatas) throw "Error: Automaton incorrect index";
    delete automatas[id];
    automatas[id] = new Automata(c, t, n, nb, na, d, a, y);
}

//Ajout d'un automate à la fin du tableau d'automates
void AutomataManager::addAutomata(CellState** c, TransitionStrategy* t, NeighborhoodStrategy* n, int nb, string na, string d, string a, int y) {
    if(nbAutomatas >= nbMaxAutomatas) throw "Error : can't be added because the automaton table is full";
    automatas[nbAutomatas] = new Automata(c, t, n, nb, na, d, a, y);
    nbAutomatas++;
}

//Supression d'un automate à un indice donné, réajustement tableau pour éviter les trous
void AutomataManager::removeAutomata(int id) {
    if(id >= nbAutomatas) throw "Error: Automaton incorrect index";
    delete automatas[id];
    //On décale les automates pour combler la supression
    while(id < nbAutomatas - 1) {
        automatas[id] = automatas[id + 1];
        id++;
    }
    delete automatas[id];
    automatas[id] = nullptr;
    nbAutomatas--;
}




