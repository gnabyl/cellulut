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
	virtual Cell calcNextCell(const Cell, const Cell**, int, CellState**, int) const = 0;
};

class TransitionContext{ //context
	TransitionStrategy* strategy;
public:
	TransitionContext(TransitionStrategy* s = nullptr) : strategy(s){}
	void setStrategy(TransitionStrategy* s);
	Cell NextCell(const Cell c, const Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates) const{strategy.calcNextCell(c, neighbors, neighborSize, availableStates, nbStates);}
	~TransitionContext(){delete strategy;}
};

class TotalisticTransition : public TransitionStrategy{
	/*Add here some properties that provide a description of the transition rule*/
	virtual Cell calcNextCell(const Cell, const Cell**, int, CellState**, int) const;
public:
	TotalisticTransition(/*Initialize the properties described above.*/);
};


class StochasticTransition : public TransitionStrategy{

};

class OuterTotalisticTransition : public TotalisticTransition{

};

///Concrete strategies///

class GOLTransition : public TotalisticTransition{
	Cell calcNextCell(const Cell, const Cell**, int, CellState**, int) const override;
};