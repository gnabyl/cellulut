#include gridd.h
 Grid::~Grid(){
    delete[][] cells;
}
Grid::Grid(cellstate c, int w=0,int h=0){
    this->width=w;
    this->height=h;
    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
            Cells[i][j]=new Cell(c,i,j)
        }
    }
}
Gridd::Grid(const Grid& g):widht(g.width), height(g.height), cell(new **cell){
    for(int i=0;i<g.width;i++){
        for(int j=0;j<g.height;j++){
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
        cell** newcells= new **cell;
        for(int i=0;i<width;i++){
            for(int j=0;j<height;j++){
                newcells[i][j]=g.cells[i][j]
            }
        }
        cell** oldcells=this->cells;
        this->cells=newcells;
        delete[][] oldcells;
    }
    return *this;
}

int Gridd::getwidth() const{
    return this->width;
}
int Grid::getheight() const{
    return this->height;
}

void Grid::setCell(cellstate c,int x,int y)
{
    this->cells[x][y].setstate(c);
}

cell& Grid::getCell(int x , int y) const
{
    return this->cells[x][y];
}