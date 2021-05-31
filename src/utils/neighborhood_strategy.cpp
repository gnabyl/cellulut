//
// Created by Téva Ducoté on 23/04/2021.
//

#include "neighborhood_strategy.h"
#include <cmath>

VonNeumannNeighborhood::VonNeumannNeighborhood(){
    neighbors = new Cell* [nbNeighbors];

}


Cell** VonNeumannNeighborhood::getNeighbors(Cell *c, Grid *g) {
    int n=0;
    for (int k = c->getX() - 1; k <= c->getX() + 1 ; k++) {
        for (int l = c->getY() - 1; l <= c->getY()+ 1 ; l++) {
            //coordonnée cellule voisine
            int x = (k + g->getHeight()) % g->getHeight();
            int y = (l + g->getWidth()) % g->getWidth();
            if((abs(x - c->getX()) + abs(y - c->getY())) == 1) {
                neighbors[n] = g->getCell(x, y);
                n++;
            }
        }
    }
    return neighbors;
}

VonNeumannNeighborhoodGeneralized::VonNeumannNeighborhoodGeneralized(int radius){
    this->radius = radius;
    this->nbNeighbors = this->radius * this->radius + (this->radius + 1) * ((this->radius + 1)) - 1 ;
    neighbors = new Cell* [nbNeighbors];
}


Cell** VonNeumannNeighborhoodGeneralized::getNeighbors(Cell *c, Grid *g) {
    int n=0;
    for (int k = c->getX() - 1; k <= c->getX() + 1 ; k++) {
        for (int l = c->getY() - 1; l <= c->getY()+ 1 ; l++) {
            //coordonnée cellule voisine
            int x = (k + g->getHeight()) % g->getHeight();
            int y = (l + g->getWidth()) % g->getWidth();
            if((abs(x - c->getX()) + abs(y - c->getY())) > 0 && (abs(x - c->getX()) + abs(y - c->getY()))<=radius) {
                neighbors[n] = g->getCell(x, y);
                n++;
            }
        }
    }
    return neighbors;
}

MooreNeighborhood::MooreNeighborhood() {
    neighbors = new Cell* [nbNeighbors];
}

Cell** MooreNeighborhood::getNeighbors(Cell *c, Grid *g) {
    int n=0;
    for (int k = c->getX() - 1; k <= c->getX() + 1 ; k++) {
        for (int l = c->getY() - 1; l <= c->getY()+ 1 ; l++) {
            //coordonnée cellule voisine
            int x = (k + g->getHeight()) % g->getHeight();
            int y = (l + g->getWidth()) % g->getWidth();
            if(x != c->getX() || y !=c->getY()) {
                neighbors[n] = g->getCell(x, y);
                n++;
            }
        }
    }
    return neighbors;
}

MooreNeighborhoodGeneralized::MooreNeighborhoodGeneralized(int radius) {
    this->radius = radius;
    this->nbNeighbors = (2 * this->radius + 1) * (2 * this->radius + 1) - 1;
    neighbors = new Cell* [nbNeighbors];
}

Cell** MooreNeighborhoodGeneralized::getNeighbors(Cell *c, Grid *g) {
    int n=0;
    for (int k = c->getX() - radius; k <= c->getX() + radius; k++) {
        for (int l = c->getY() - radius; l <= c->getY()+ radius; l++) {
            //coordonnée cellule voisine
            int x = (k + g->getHeight()) % g->getHeight();
            int y = (l + g->getWidth()) % g->getWidth();
            if(x != c->getX() || y !=c->getY()) {
                neighbors[n] = g->getCell(x, y);
                n++;
            }
        }
    }
    return neighbors;
}

//dx = [3 -3 2 2] : transmis par frontend
//dy = [2 2 -3 3] : transmis par frontend
//nbvoisin
//        getX + dx[i], getY + dy[i]


//ArbitraryNeighborhood:: ArbitraryNeighborhood(int nbNeighbors){
//      this->nbNeighbors = nbNeighbors;
//      neighbors = new Cell* [nbNeighbors];
//}

//dx et dy tableaux contenant le décalage par rapport à une cellule
//Cell** ArbitraryNeighborhood::getNeighbors(Cell *c, Grid *g, int* dx, int* dy) {
//    int n=0;
//    while(dx!=nullptr && dy!=nullptr){
            //coordonnée cellule voisine
//            int x = (dx->value+ g->getHeight()) % g->getHeight();
//            int y = (dy->value + g->getWidth()) % g->getWidth();

//                neighbors[n] = g->getCell(x, y);
//                n++;
//                dx=dx->next;
//                dy=dy->next;
//        }
//    return neighborhood[m];
//}