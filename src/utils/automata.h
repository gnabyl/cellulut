#ifndef LO21_AUTOMATA_H
#define LO21_AUTOMATA_H
#include <string>
#include <iostream>
#include "transition_strategy.h"
#include "neighborhood_strategy.h"
#include "cell_state.h"
#include "grid.h"
using namespace std;

class Automata {
  private:
    string name;
    string description;
    string author;
    int creationYear;
    CellState** availableStates = nullptr; //Différents états que les cellules peuvent prendre pour cet automate
    int nbStates;
    TransitionStrategy* transitionStrategy; //Interface fonction de transition de l'automate
    NeighborhoodStrategy* neighborStrategy; //Interface voisinage de l'automate

    //Methodes privées car gérées par AutomataManager
    Automata& operator=(const Automata& a) = default;
    Automata(const Automata&) = default;
    Automata(CellState** c, TransitionStrategy* t, NeighborhoodStrategy* n, int nb = 0, string na = "", string d = "", string a = "", int y = 2021);
    ~Automata();

    friend class AutomataManager;

  public:
    Grid& applyTransition(const Grid& src) const;

    //Getters & Setters
    void setName(const string n) {
        name = n;
    }
    string getName() const {
        return name;
    }
    void setDescription(const string d) {
        description = d;
    }
    string getDescription() const {
        return description;
    }
    void setAuthor(const string a) {
        author = a;
    }
    string getAuthor() const {
        return author;
    }
    void setCreationYear(const int y) {
        creationYear = y;
    }
    int getCreationYear() const {
        return creationYear;
    }
    void setAvailableStates(CellState** c, int taille);
    CellState** getAvailableStates() const {
        return availableStates;
    }
    void setAvailableState(CellState* c, const int i);
    CellState* getAvailableState(const int i) const;
    void setNbStates(const int n) {
        nbStates = n;
    }
    int getNbStates() const {
        return nbStates;
    }

    void setTransitionStrategy(TransitionStrategy* t) {
        transitionStrategy = t;
    }
    TransitionStrategy* getTransitionStrategy() const {
        return transitionStrategy;
    }
    void setNeighborhoodStrategy(NeighborhoodStrategy* n) {
        neighborStrategy = n;
    }
    NeighborhoodStrategy* getNeighborhoodStrategy() const {
        return neighborStrategy;
    }

};

#endif //LO21_AUTOMATA_H
