
#ifndef LO21_GRID_H
#define LO21_GRID_H
#include "cell_state.h"
#include "cell.h"
#include <cstdlib>
#include <ctime>

class Grid {
  private:
    int width;
    int height;
    Cell*** cells = nullptr;

  public:
    Grid(CellState* s, int w, int h);
    Grid(int nbStates, CellState** availableStates, int w, int h);
    Grid(const Grid& g);
    ~Grid();
    Grid& operator= (const Grid& g);

    void setCell(Cell* c, int x, int y);
    Cell* getCell(int x, int y) const;
    int getWidth() const;
    int getHeight() const;
};

#endif //LO21_GRID_H
