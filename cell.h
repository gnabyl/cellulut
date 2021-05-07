
#ifndef LO21_CELL_H
#define LO21_CELL_H
#include cellstate.h
class Cell{

private:
cellstate State;
int x ;
int y ;


public:
    void setstate(cellstate s);
    cellstate getstatte() const;
    Cell(cellstate s,int i , int j);


};

#endif //LO21_CELL_H
