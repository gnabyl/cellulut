#include "grid_factory.h"

template<typename Base, typename T>
inline bool instanceof(const T* ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

GridFactory::GridFactory() {}

Grid* GridFactory::generateGrid(GridType type, int width, int height, Automata* automata) {
    Grid* grid;
    switch (type) {
        case RANDOM:
            grid = new Grid(automata->getNbStates(), automata->getAvailableStates(), width, height);
            break;
        case EMPTY:
            grid = new Grid(automata->getAvailableStates()[0], width, height);
            break;
    }
    if (instanceof<LATransition>(automata->getTransitionStrategy())) {
        grid->getCell(0, 0)->setDirection(Direction::up);
    }
    return grid;
}
