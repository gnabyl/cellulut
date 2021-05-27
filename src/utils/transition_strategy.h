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
    std::string name;
  public:
    TransitionStrategy(std::string name) : name(name) {};
    virtual Cell* calcNextCell(Cell*, Cell**, int, CellState**, int) const = 0;
    std::string getName() const {
        return name;
    }
};


class TotalisticTransition : public TransitionStrategy {
  public:
    TotalisticTransition(std::string name = "Totalistic Transition") : TransitionStrategy(name) {}
    virtual Cell* calcNextCell(Cell*, Cell**, int, CellState**, int) const = 0;
};


class StochasticTransition : public TransitionStrategy {
  public:
    StochasticTransition(std::string name = "Stochastic Transition") : TransitionStrategy(name) {}
    virtual Cell* calcNextCell(Cell*, Cell**, int, CellState**, int) const = 0;
};

class OuterTotalisticTransition : public TotalisticTransition {
  public:
    OuterTotalisticTransition(std::string name = "OuterTotalistic Transition") : TotalisticTransition(name) {}
    virtual Cell* calcNextCell(Cell*, Cell**, int, CellState**, int) const = 0;
};

///Concrete strategies///
class GOLTransition : public OuterTotalisticTransition {
  public:
    GOLTransition(std::string name = "Game Of Life Transition") : OuterTotalisticTransition(name) {}
    Cell* calcNextCell(Cell*, Cell**, int, CellState**, int) const override;
};

class BBTransition : public OuterTotalisticTransition {
  public:
    BBTransition(std::string name = "Brian's Brain Transition") : OuterTotalisticTransition(name) {}
    Cell* calcNextCell(Cell*, Cell**, int, CellState**, int) const override;
};

#endif
