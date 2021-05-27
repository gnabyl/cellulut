#ifndef GRID_FACTORY_H
#define GRID_FACTORY_H

#include "grid.h"
#include "automata.h"

enum GridType {
    EMPTY,
    RANDOM
};

class GridFactory {
  public:
    GridFactory();
    Grid* generateGrid(GridType type, int width, int height, Automata* automata);
};

#endif // GRID_FACTORY_H
