#ifndef TRANSITION_STRATEGY_H
#define TRANSITION_STRATEGY_H

#include <string>
#include "neighborhood_strategy.h"
#include "cell_state.h"
#include "grid.h"

class TransitionException {
    std::string info;
  public:
    TransitionException(std::string s): info(s) {}
    std::string getInfo() {
        return info;
    }
};

////Implementation of the Strategy design pattern./////

///Basic interface///

class TransitionStrategy { //interface
  public:
    virtual Cell* calcNextCell(Cell*, Cell**, int, CellState**, int) const = 0;
};


class TotalisticTransition : public TransitionStrategy {
    virtual Cell* calcNextCell(Cell*, Cell**, int, CellState**, int) const = 0;
};


class StochasticTransition : public TransitionStrategy {
    virtual Cell* calcNextCell(Cell*, Cell**, int, CellState**, int) const = 0;
};

class OuterTotalisticTransition : public TotalisticTransition {
    virtual Cell* calcNextCell(Cell*, Cell**, int, CellState**, int) const = 0;
};

///Concrete strategies///
class GOLTransition : public OuterTotalisticTransition {
    Cell* calcNextCell(Cell*, Cell**, int, CellState**, int) const;
};

class BBTransition : public OuterTotalisticTransition {
    Cell* calcNextCell(Cell*, Cell**, int, CellState**, int) const;
};

class DGTransition : public OuterTotalisticTransition{
    Cell* calcNextCell(Cell* c, Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates) const;
};

class LLTransition : public OuterTotalisticTransition{
    Cell* calcNextCell(Cell* c, Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates) const;
};


class LATransition : public OuterTotalisticTransition{
    Cell* calcNextCell(Cell* c, Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates) const;
};


#endif
