
#ifndef LO21_CELL_H
#define LO21_CELL_H
#include cellstate.h
class Cell{

private:
cellstate State;

public:
    void setstate(cellstate s);
    cellstate getstatte() const;

};

#endif //LO21_CELL_H
