#ifndef LO21_CELL_H
#define LO21_CELL_H
#include "cell_state.h"

enum Direction {NONE, UP, RIGHT, DOWN, LEFT};

class Cell {
  private:
    CellState* state;
    int x;
    int y;
    Direction dir;

  public:
    void setState(CellState* s);
    CellState* getState() const;
    Cell(CellState* s, int i, int j, Direction d = NONE);
    Cell(const Cell&);
    int getX() const;
    int getY() const;
    Direction getDirection() const;
    void setDirection(Direction d);
};

#endif //LO21_CELL_H
