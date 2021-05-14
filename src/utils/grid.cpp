#include "grid.h"

 Grid::~Grid(){
    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
            delete cells[i][j];
    delete[] cells;
    cells = nullptr;
}

Grid::Grid(CellState c, int w=0,int h=0){
    this->width=w;
    this->height=h;
    cells = new Cell**[h];
    for(int i=0;i<h;i++) cells[i]=new Cell*[w];
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            cells[i][j]=new Cell(c,i,j);
        }
    }
}
Grid::Grid(const Grid& g):widht(g.width), height(g.height), cell(new Cell**[g.height]){
    for(int i=0;i<g.height;i++){
        for(int j=0;j<g.width;j++){
            this->cells[i][j]=g.cells[i][j]
        }
    }

}


Grid& Gridd::operator= (const Grid& g)
{
    if(this!=&g)
    {
        if (this->width!=g.width)
        {
            this->width=g.width;
        }
        if( this->height!=g.height)
        {
            this->height=g.height;
        }
        Cell*** newcells= new Cell**[g.height];
        for(int i=0;i<g.height;i++) newcells[i]=new Cell*[g.width];
        for(int i=0;i<width;i++){
            for(int j=0;j<height;j++){
                newcells[i][j]=g.cells[i][j];
            }
        }
        for(int i=0;i<height;i++)
            for(int j=0;j<width;j++)
                delete cells[i][j];
        delete[] cells;
        this->cells=newcells;
    }
    return *this;
}

size_t Grid::getWidth() const {
    return this->width;
}
size_t Grid::getHeight() const{
    return this->height;
}

void Grid::setCell(Cell *c,int x,int y)
{
    delete this->cells[x][y];
    this->cells[x][y]=c;
}

Cell* Grid::getCell(int x , int y) const
{
    return this->cells[x][y];
}
