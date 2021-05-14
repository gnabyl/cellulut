#include "cell.h"
#include "cellstate.h"

void Cell::setstate(CellState s){
   this->State=s;
}
CellState Cell::getState() const{
    return this->State;
}

Cell::Cell(Cellstate s, int x , int y):state(s),x(x),y(y){}


