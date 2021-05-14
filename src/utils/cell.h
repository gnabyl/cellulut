#ifndef LO21_CELL_H
#define LO21_CELL_H
#include "cell_state.h"

class Cell{
private:
    CellState *state;
    int x;
    int y;

public:
    void setState(CellState *s);
    CellState* getState() const;
    Cell(CellState *s,int i , int j);
    int getX() const;
    int getY() const;
};

#endif //LO21_CELL_H
