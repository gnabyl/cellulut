
#ifndef LO21_GRID_H
#define LO21_GRID_H
#include "cell_state.h"
#include "cell.h"

class Grid{
private:
    Cell **cells=nullptr;
    int width;
    int height;

public:
    Grid(Cellstate s, int w=0,int h=0);
    Grid(const Grid& g);
    ~Grid();
    Grid& operator= (const Grid& g);

    void setCell(Cell c,int x,int y);
    Cell& getCell(int x , int y) const;
    int getwidth() const;
    int getheight() const;
};
#endif //LO21_GRID_H
