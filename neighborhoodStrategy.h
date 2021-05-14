//
// Created by Téva Ducoté on 23/04/2021.
//

#ifndef LO21_NEIGHBORHOODSTRATEGY_H
#define LO21_NEIGHBORHOODSTRATEGY_H
#include<utility>
#include "cell.h"
#include "grid.h"
#include "cellstate.h"

class NeighborhoodStrategy{
public:
    virtual Cell*** getNeighborhood() const = 0;
    virtual unsigned int getNbNeighbors()const=0 ;
};

class VonNeumannNeighborhood: public NeighborhoodStrategy{
    Cell*** neighborhood;
    unsigned int nb_neighbors=4;
public:
    VonNeumannNeighborhood(const Grid g );
    unsigned int getNbNeighbors() const { return nb_neighbors;}
    Cell*** getNeighborhood() const {return neighborhood;}
};

class VonNeumannNeighborhoodGeneralized: public NeighborhoodStrategy{
    Cell*** neighborhood;
    unsigned int radius;
    unsigned int nb_neighbors;
public:
    VonNeumannNeighborhoodGeneralized(const Grid g, unsigned int radius=1);
    unsigned int getNbNeighbors() const { return nb_neighbors;}
    Cell*** getNeighborhood() const {return neighborhood;}
};
class MooreNeighborhood: public NeighborhoodStrategy{
    Cell*** neighborhood;
    unsigned int nb_neighbors=8;
public:
    MooreNeighborhood(const Grid g);
    unsigned int getNbNeighbors() const { return nb_neighbors;}
    Cell*** getNeighborhood() const {return neighborhood;}
};

class MooreNeighborhoodGeneralized: public NeighborhoodStrategy{
    Cell*** neighborhood;
    unsigned int radius;
    unsigned int nb_neighbors;
public:
    MooreNeighborhoodGeneralized(const Grid g, unsigned int radius=1);
    unsigned int getNbNeighbors() const { return nb_neighbors;}
    Cell*** getNeighborhood() const {return neighborhood;}
};

class ArbitraryNeighborhood: public NeighborhoodStrategy{
    Cell*** neighborhood;
    unsigned int nb_neighbors;
public:
    ArbitraryNeighborhood(const Grid g);
    unsigned int getNbNeighbors() const { return nb_neighbors;}
    Cell*** getNeighborhood() const {return neighborhood;}}
};

#endif //LO21_NEIGHBORHOODSTRATEGY_H
