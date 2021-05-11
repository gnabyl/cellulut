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
    virtual Cell** getNeighborhood() const = 0;
};

class VonNeumannNeighborhood: public NeighborhoodStrategy{
    Cell*** getNeighborhood();
    int nb_neighbors=4;
public:
    VonNeumannNeighborhood(const int hauteur,const int largeur );
};

class VonNeumannNeighborhoodGeneralized: public NeighborhoodStrategy{
    Cell*** neighborhood;
    unsigned int radius;
    unsigned int nb_neighbors;
public:
    VonNeumannNeighborhoodGeneralized(const int hauteur,const int largeur, unsigned int radius=1);

};
class MooreNeighborhood: public NeighborhoodStrategy{
    Cell*** neighborhood;
    int nb_neighbors=8;
public:
    MooreNeighborhood(const int hauteur,const int largeur);
};

class MooreNeighborhoodGeneralized: public NeighborhoodStrategy{
    Cell*** neighborhood;
    unsigned int radius;
    unsigned int nb_neighbors;
public:
    MooreNeighborhoodGeneralized(const int hauteur,const int largeur, unsigned int radius=1);
};

class ArbitraryNeighborhood: public NeighborhoodStrategy{
    Cell*** neighborhood;
    unsigned int nb_neighbors;
public:
    ArbitraryNeighborhood(const int hauteur,const int largeur);
};

#endif //LO21_NEIGHBORHOODSTRATEGY_H
