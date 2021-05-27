#include "grid_factory.h"

GridFactory::GridFactory() {}

Grid* GridFactory::generateGrid(GridType type, int width, int height, Automata* automata, bool showAnt, int antX, int antY) {
    Grid* grid;
    switch (type) {
        case RANDOM:
            grid = new Grid(automata->getNbStates(), automata->getAvailableStates(), width, height);
            break;
        case EMPTY:
            grid = new Grid(automata->getAvailableStates()[0], width, height);
            break;
    }
    if (showAnt) {
        grid->getCell(antX, antY)->getState()->setDirection(direction::up);
    }
    return grid;
}
