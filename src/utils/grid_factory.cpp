#include "grid_factory.h"

template<typename Base, typename T>
inline bool instanceof(const T*) {
    return std::is_base_of<Base, T>::value;
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
        std::cout << "we have an ant\n";
        grid->getCell(0, 0)->getState()->setDirection(Direction::up);
    }
    return grid;
}
