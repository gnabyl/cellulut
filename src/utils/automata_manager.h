#ifndef LO21_AUTOMATAMANAGER_H
#define LO21_AUTOMATAMANAGER_H
#include <iostream>
#include "automata.h"
#include "transition_strategy.h"
#include "neighborhood_strategy.h"
#include "cell_state.h"
#include "grid.h"

#define MAX_AUTOMATA 1000

using namespace std;

class AutomataManager {
  private:
    static AutomataManager* instance; //Instance unique (singleton)
    int nbAutomatas;
    const int nbMaxAutomatas = MAX_AUTOMATA;
    Automata** automatas;

    AutomataManager(const AutomataManager& a) = delete;
    AutomataManager();
    ~AutomataManager();
    void operator=(const AutomataManager& a) = delete;

  public:
    static AutomataManager* getAutomataManager();
    static void destroyAutomataManager();

    Automata* getAutomata(int id) const;
    void changeAutomata(int id, CellState** c, TransitionStrategy* t, NeighborhoodStrategy* n, int nb = 0, string na = "", string d = "", string a = "", int y = 2021);
    void addAutomata(CellState** c, TransitionStrategy* t, NeighborhoodStrategy* n, int nb = 0, string na = "", string d = "", string a = "", int y = 2021);
    void removeAutomata(int id);

    int getNbAutomatas() const {
        return nbAutomatas;
    }
};

#endif //LO21_AUTOMATAMANAGER_H
