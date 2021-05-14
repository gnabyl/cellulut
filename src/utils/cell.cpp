#include "cell.h"
#include "cell_state.h"

void Cell::setState(CellState *s){
   this->state=s;
}
CellState* Cell::getState() const{
    return this->state;
}

Cell::Cell(CellState *s, int x , int y):state(s),x(x),y(y){}


int Cell::getX() const {
    return this->x;
}

int Cell::getY() const {
    return this->x;
}
