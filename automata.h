#ifndef LO21_AUTOMATA_H
#define LO21_AUTOMATA_H
#include <string>
#include <iostream>
//#include "transition-strategy.h"
//#include "neighbor-strategy.h"
//#include "cellState.h"
//#include "grid.h"
using namespace std;

class Automata
{
private:
    string name;
    string description;
    string author;
    size_t creationYear;
    CellState** availableStates =nullptr; //Différents états que les cellules peuvent prendre pour cet automate
    size_t nbStates;
    ITransitionStrategy transitionStrategy; //Interface fonction de transition de l'automate
    INeighborStrategy neighborStrategy; //Interface voisinage de l'automate

    //Methodes privés car gérées par AutomataManager
    void operator=(const Automata& a)= delete;
    Automata(const Automata& a)= delete;
    Automata(CellState** c,ITransitionStrategy t,INeighborStrategy n,size_t nb=0,string na="", string d="",string a="",size_t y=2021);
    ~Automata();

    friend class AutomataManager;
public:
    void applyTransition(const Grid& src, Grid& dest) const;

    //Getters & Setters
    void setName(const string n){ name=n;}
    string getName() const {return name;}
    void setDescription(const string d){description=d;}
    string getDescription() const {return description;}
    void setAuthor(const string a){ author=a;}
    string getAuthor() const {return author;}
    void setCreationYear(const size_t y){ creationYear=y;}
    size_t getCreationYear() const {return creationYear;}
    void setAvailableStates(const CellStates** c);
    CellState** getAvailableStates() const {return availableStates;}
    void setAvailableState(const CellState* c,const size_t i);
    CellState* getAvailableState(const size_t i) const;
    void setNbStates(const size_t n){nbStates=n;}
    size_t getNbStates() const {return nbStates;}

    //C'est des setters et getters classiques pour les strategy ?
    void setTransitionStrategy(const ITransitionStrategy t){transitionStrategy=t;}
    ITransitionStrategy getTransitionStrategy() const {return transitionStrategy;}
    void setNeighborStrategy(const INeighborStrategy n){neighborStrategy=n;}
    INeighborStrategy getNeighborStrategy() const {return neighborStrategy;}

};

#endif //LO21_AUTOMATA_H
