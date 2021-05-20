//
// Created by Téva Ducoté on 23/04/2021.
//

#ifndef LO21_NEIGHBORHOODSTRATEGY_H
#define LO21_NEIGHBORHOODSTRATEGY_H

#include <iostream>
#include<utility>
#include "cell.h"
#include "grid.h"
#include "cell_state.h"

class NeighborhoodStrategy {
  public:
    virtual Cell** getNeighbors(Cell *c, Grid *g) = 0;
    virtual int getNbNeighbors() const = 0 ;
};

class VonNeumannNeighborhood: public NeighborhoodStrategy {
    Cell** neighbors;
    int nbNeighbors = 4;
  public:
    VonNeumannNeighborhood();
    ~VonNeumannNeighborhood() {
        delete[] neighbors;
    }
    int getNbNeighbors() const {
        return nbNeighbors;
    }
    Cell** getNeighborhood() const {
        return neighbors;
    }
    virtual Cell** getNeighbors(Cell *c, Grid *g);
};

class VonNeumannNeighborhoodGeneralized: public NeighborhoodStrategy {
    Cell** neighbors;
    int radius;
    int nbNeighbors;
  public:
    VonNeumannNeighborhoodGeneralized(int radius = 1);
    ~VonNeumannNeighborhoodGeneralized() {
        delete[] neighbors;
    }
    int getNbNeighbors() const {
        return nbNeighbors;
    }
    Cell** getNeighborhood() const {
        return neighbors;
    }
    virtual Cell** getNeighbors(Cell *c, Grid *g);
};
class MooreNeighborhood: public NeighborhoodStrategy {
    Cell** neighbors;
    int nbNeighbors = 8;
  public:
    MooreNeighborhood();
    ~MooreNeighborhood() {
        delete[] neighbors;
    }
    int getNbNeighbors() const {
        return nbNeighbors;
    }
    virtual Cell** getNeighbors(Cell *c, Grid *g);
};

class MooreNeighborhoodGeneralized: public NeighborhoodStrategy {
    Cell** neighbors;
    int radius;
    int nbNeighbors;
  public:
    MooreNeighborhoodGeneralized(int radius = 1);
    ~MooreNeighborhoodGeneralized() {
        delete[] neighbors;
    }
    int getNbNeighbors() const {
        return nbNeighbors;
    }
    virtual Cell** getNeighbors(Cell *c, Grid *g);
};

class ArbitraryNeighborhood: public NeighborhoodStrategy {
    Cell** neighborhood;
    int nbNeighbors;
    int nbCells;
  public:
    ArbitraryNeighborhood(const Grid g);
    ~ArbitraryNeighborhood() {
        delete[] neighborhood;
    }
    int getNbNeighbors() const {
        return nbNeighbors;
    }
    Cell** getNeighborhood() const {
        return neighborhood;
    }
    virtual Cell** getNeighbors(Cell *c, Grid *g);
};

#endif //LO21_NEIGHBORHOODSTRATEGY_H
