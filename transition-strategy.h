#ifndef TRANSITION_STRATEGY_H
#define TRANSITION_STRATEGY_H

#include <iostream>
#include <string>
#include "automata.h"
#include "neighbor-strategy.h"
#include "cellstate.h"
#include "grid.h"

class TransitionException{
	std::string info;
public:
	TransitionException(std::string s): info(s){}
	getInfo(){return info;}
};

////Implementation of the Strategy design pattern./////

///Basic interface///

class TransitionStrategy{ //interface
public:
	virtual Cell calcNextCell(const Cell, const Cell**, int, CellState**, int) const = 0;
};


class TotalisticTransition : public TransitionStrategy{
	virtual Cell calcNextCell(const Cell, const Cell**, int, CellState**, int) const;
};


class StochasticTransition : public TransitionStrategy{
	virtual Cell calcNextCell(const Cell, const Cell**, int, CellState**, int) const;
};

class OuterTotalisticTransition : public TotalisticTransition{
	virtual Cell calcNextCell(const Cell, const Cell**, int, CellState**, int) const;
};

///Concrete strategies///
class GOLTransition : public OuterTotalisticTransition{
	Cell calcNextCell(const Cell, const Cell**, int, CellState**, int) const;
};

class BBTransition : public OuterTotalisticTransition{
	Cell calcNextCell(const Cell, const Cell**, int, CellState**, int) const;
};