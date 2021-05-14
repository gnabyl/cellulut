#ifndef LO21_CELL_H
#define LO21_CELL_H
#include "cell_state.h"

class Cell{
private:
	CellState State;
	int x ;
	int y ;

public:
    void setstate(CellState s);
    CellState getState() const;
    Cell(CellState s,int i , int j);
};

#endif //LO21_CELL_H
