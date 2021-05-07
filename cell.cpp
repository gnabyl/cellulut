#include cell.h
#include cellstate.h
void Cell::setstate(cellstate s){
   this->State=s;
}
Cellstate Cell::getstate(){
    return this->State
}

Cell::Cell(Cellstate s, int x , int y):state(s),x(x),y(y){}


