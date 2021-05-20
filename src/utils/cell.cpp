#include "cell.h"
#include "cell_state.h"

void Cell::setState(CellState* s) {
    this->state = s;
}
CellState* Cell::getState() const {
    return this->state;
}

Cell::Cell(CellState* s, int x, int y): state(s), x(x), y(y) {}

Cell::Cell(const Cell& c): state(c.getState()), x(c.getX()), y(c.getY()){}


int Cell::getX() const {
    return this->x;
}

int Cell::getY() const {
    return this->y;
}
