#include <iostream>
#include <string>

class TransitionStrategy{
public:
	calcNextCell(Cell c, Cell** neighbors){}
};

class TotalisticTransition : public TransitionStrategy{

};

class StochasticTransition : public TransitionStrategy{

};