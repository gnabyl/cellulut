
#ifndef LO21_GRID_H
#define LO21_GRID_H
#include "cell_state.h"
#include "cell.h"

class Grid{
private:
    size_t width;
    size_t height;
    Cell ***cells=nullptr;

public:
    Grid(CellState *s, size_t w=0, size_t h=0);
    Grid(const Grid& g);
    ~Grid();
    Grid& operator= (const Grid& g);

    void setCell(Cell *c,int x,int y);
    Cell* getCell(int x , int y) const;
    size_t getWidth() const;
    size_t getHeight() const;
};
#endif //LO21_GRID_H
