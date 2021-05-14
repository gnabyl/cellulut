#include "cell.h"
#include "cell_state.h"

void Cell::setstate(CellState s){
   this->State=s;
}
CellState Cell::getState() const{
    return this->State;
}

Cell::Cell(Cellstate s, int x , int y):state(s),x(x),y(y){}


