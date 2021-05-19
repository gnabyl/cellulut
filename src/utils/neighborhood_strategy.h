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
    virtual Cell*** getNeighborhood() const = 0;
    virtual Cell** getNeighbors(Cell *c, Grid *g) = 0;
    virtual int getNbNeighbors() const = 0 ;
};

class VonNeumannNeighborhood: public NeighborhoodStrategy {
    Cell*** neighborhood;
    int nbNeighbors = 4;
    int nbCells;
  public:
    VonNeumannNeighborhood(const Grid g );
    ~VonNeumannNeighborhood() {
        for(int i = 0; i < nbCells; i++ ) delete[] neighborhood[i];
        delete[] neighborhood;
    }
    int getNbNeighbors() const {
        return nbNeighbors;
    }
    Cell*** getNeighborhood() const {
        return neighborhood;
    }
    virtual Cell** getNeighbors(Cell *c, Grid *g);
};

class VonNeumannNeighborhoodGeneralized: public NeighborhoodStrategy {
    Cell*** neighborhood;
    int radius;
    int nbNeighbors;
    int nbCells;
  public:
    VonNeumannNeighborhoodGeneralized(const Grid g, int radius = 1);
    ~VonNeumannNeighborhoodGeneralized() {
        for(int i = 0; i < nbCells; i++ ) delete[] neighborhood[i];
        delete[] neighborhood;
    }
    int getNbNeighbors() const {
        return nbNeighbors;
    }
    Cell*** getNeighborhood() const {
        return neighborhood;
    }
    virtual Cell** getNeighbors(Cell *c, Grid *g);
};
class MooreNeighborhood: public NeighborhoodStrategy {
    Cell*** neighborhood;
    int nbNeighbors = 8;
    int nbCells;
  public:
    MooreNeighborhood(Grid* g);
    ~MooreNeighborhood() {
        for(int i = 0; i < nbCells; i++ ) delete[] neighborhood[i];
        delete[] neighborhood;
    }
    int getNbNeighbors() const {
        return nbNeighbors;
    }
    Cell*** getNeighborhood() const {
        return neighborhood;
    }
    virtual Cell** getNeighbors(Cell *c, Grid *g);
};

class MooreNeighborhoodGeneralized: public NeighborhoodStrategy {
    Cell*** neighborhood;
    int radius;
    int nbNeighbors;
    int nbCells;
  public:
    MooreNeighborhoodGeneralized(const Grid g, int radius = 1);
    ~MooreNeighborhoodGeneralized() {
        for(int i = 0; i < nbCells; i++ ) delete[] neighborhood[i];
        delete[] neighborhood;
    }
    int getNbNeighbors() const {
        return nbNeighbors;
    }
    Cell*** getNeighborhood() const {
        return neighborhood;
    }
    virtual Cell** getNeighbors(Cell *c, Grid *g);
};

class ArbitraryNeighborhood: public NeighborhoodStrategy {
    Cell*** neighborhood;
    int nbNeighbors;
    int nbCells;
  public:
    ArbitraryNeighborhood(const Grid g);
    ~ArbitraryNeighborhood() {
        for(int i = 0; i < nbCells; i++ ) delete[] neighborhood[i];
        delete[] neighborhood;
    }
    int getNbNeighbors() const {
        return nbNeighbors;
    }
    Cell*** getNeighborhood() const {
        return neighborhood;
    }
    virtual Cell** getNeighbors(Cell *c, Grid *g);
};

#endif //LO21_NEIGHBORHOODSTRATEGY_H
