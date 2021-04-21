#include <iostream>
#include <string>

class TransitionException{
	std::string info;
public:
	TransitionException(std::string s): info(s){}
	getInfo(return info;)
};

////Implementation of the Strategy design pattern./////

///Basic interface///

class TransitionStrategy{ //interface
public:
	Cell calcNextCell(const Cell, const Cell**, int, CellState**, int);
};

class TransitionContext{ //context
	TransitionStrategy strategy;
public:
	setStrategy(TransitionStrategy s){strategy = s;}
	Cell NextCell(const Cell c, const Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates){strategy.calcNextCell(c, neighbors, neighborSize, availableStates, nbStates);}
};

//Careful: the following classes are still abstract, even though inherited from TransitionStrategy.

class TotalisticTransition : public TransitionStrategy{

};


class StochasticTransition : public TransitionStrategy{

};

class OuterTotalisticTransition : public TotalisticTransition{

};

///Concrete strategies///

class GOLTransition : public TotalisticTransition{
	Cell calcNextCell(const Cell, const Cell**, int, CellState**, int);
};