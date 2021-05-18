//
// Created by Téva Ducoté on 23/04/2021.
//

#include "neighborhood_strategy.h"
#include <cmath>

VonNeumannNeighborhood::VonNeumannNeighborhood(const Grid g): nbCells(g.getHeight() * g.getWidth()) {
    neighborhood = new Cell** [g.getHeight()*g.getWidth()];
    for (int i = 0; i < g.getHeight()*g.getWidth() ; i++) {
        neighborhood[i] = new Cell*[this->nbNeighbors];
    }
}


Cell** VonNeumannNeighborhood::getNeighbors(Cell *c, Grid *g) {
    int m=((c->getX()-1)*g->getWidth())+c->getY();
    int n=0;
    for (int k = c->getX() - 1; k <= c->getX() + 1 ; k++) {
        for (int l = c->getY() - 1; l <= c->getY()+ 1 ; l++) {
            //coordonnée cellule voisine
            int x = (k + g->getHeight()) % g->getHeight();
            int y = (l + g->getWidth()) % g->getWidth();
            if((abs(x - c->getX()) + abs(y - c->getY())) == 1) {
                neighborhood[m][n] = g->getCell(x, y);
                n++;
            }
        }
    }
    return neighborhood[m];
}

VonNeumannNeighborhoodGeneralized::VonNeumannNeighborhoodGeneralized(const Grid g, int radius): nbNeighbors(radius * radius + (radius + 1) * ((radius + 1)) - 1 ), nbCells(g.getHeight() * g.getWidth()) {
    neighborhood = new Cell** [g.getHeight()*g.getWidth()];
    for (int i = 0; i < g.getHeight()*g.getWidth() ; i++) {
        neighborhood[i] = new Cell*[this->nbNeighbors];
    }
}


Cell** VonNeumannNeighborhoodGeneralized::getNeighbors(Cell *c, Grid *g) {
    int m=((c->getX()-1)*g->getWidth())+c->getY();
    int n=0;
    for (int k = c->getX() - 1; k <= c->getX() + 1 ; k++) {
        for (int l = c->getY() - 1; l <= c->getY()+ 1 ; l++) {
            //coordonnée cellule voisine
            int x = (k + g->getHeight()) % g->getHeight();
            int y = (l + g->getWidth()) % g->getWidth();
            if((abs(x - c->getX()) + abs(y - c->getY())) > 0 && (abs(x - c->getX()) + abs(y - c->getY()))<=radius) {
                neighborhood[m][n] = g->getCell(x, y);
                n++;
            }
        }
    }
    return neighborhood[m];
}

MooreNeighborhood::MooreNeighborhood(Grid *g): nbCells(g->getHeight() * g->getWidth()) {
    neighborhood = new Cell** [g->getHeight()*g->getWidth()];
    for (int i = 0; i < g->getHeight()*g->getWidth() ; i++) {
        neighborhood[i] = new Cell*[this->nbNeighbors];
    }
}



Cell** MooreNeighborhood::getNeighbors(Cell *c, Grid *g) {
    int m=((c->getX()-1)*g->getWidth())+c->getY();
    int n=0;
    for (int k = c->getX() - 1; k <= c->getX() + 1 ; k++) {
        for (int l = c->getY() - 1; l <= c->getY()+ 1 ; l++) {
            //coordonnée cellule voisine
            int x = (k + g->getHeight()) % g->getHeight();
            int y = (l + g->getWidth()) % g->getWidth();
            if(x != c->getX()||y !=c->getY()) {
                neighborhood[m][n] = g->getCell(x, y);
                n++;
            }
        }
    }
    return neighborhood[m];
}

MooreNeighborhoodGeneralized::MooreNeighborhoodGeneralized(const Grid g, int radius): nbNeighbors((2 * radius + 1) * (2 * radius + 1) - 1), nbCells(g.getHeight() * g.getWidth()) {
    neighborhood = new Cell** [g.getHeight()*g.getWidth()];
    for (int i = 0; i < g.getHeight()*g.getWidth() ; i++) {
        neighborhood[i] = new Cell*[this->nbNeighbors];
    }
}

Cell** MooreNeighborhoodGeneralized::getNeighbors(Cell *c, Grid *g) {
    int m=((c->getX()-1)*g->getWidth())+c->getY();
    int n=0;
    for (int k = c->getX() - 1; k <= c->getX() + 1 ; k++) {
        for (int l = c->getY() - 1; l <= c->getY()+ 1 ; l++) {
            //coordonnée cellule voisine
            int x = (k + g->getHeight()) % g->getHeight();
            int y = (l + g->getWidth()) % g->getWidth();
            if(0 < abs(x - c->getX()) && 0 < abs(y - c->getY()) && abs(x - c->getX()) <=radius && abs(y - c->getY()) <= radius) {
                neighborhood[m][n] = g->getCell(x, y);
                n++;
            }
        }
    }
    return neighborhood[m];
}

//dx = [3 -3 2 2] : transmis par frontend
//dy = [2 2 -3 3] : transmis par frontend
//nbvoisin
//        getX + dx[i], getY + dy[i]


//ArbitraryNeighborhood:: ArbitraryNeighborhood(const Grid g): nbCells(g.getHeight() * g.getWidth()),nbNeighbors(/* faire lien avec front*/) {
//    neighborhood = new Cell** [g.getHeight()*g.getWidth()];
//    for (int i = 0; i < g.getHeight()*g.getWidth() ; i++) {
//        neighborhood[i] = new Cell*[this->nbNeighbors];
//    }
//}

//dx et dy tableaux contenant le décalage par rapport à une cellule
//Cell** ArbitraryNeighborhood::getNeighbors(Cell *c, Grid *g,tab* dx, tab* dy) {
//    int m=((c->getX()-1)*g->getWidth())+c->getY();
//    int n=0;
//    while(dx!=nullptr && dy!=nullptr){
            //coordonnée cellule voisine
//            int x = (dx->value+ g->getHeight()) % g->getHeight();
//            int y = (dy->value + g->getWidth()) % g->getWidth();

//                neighborhood[m][n] = g->getCell(x, y);
//                n++;
//                dx=dx->next;
//                dy=dy->next;
//        }
//    return neighborhood[m];
//}
