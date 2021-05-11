//
// Created by Téva Ducoté on 23/04/2021.
//

#ifndef LO21_NEIGHBORHOODSTRATEGY_H
#define LO21_NEIGHBORHOODSTRATEGY_H
#include<utility>
class NeighborhoodStrategy{
public:
    getNeighborhood();
};
class VonNeumannNeighborhood: public NeighborhoodStrategy{
    std::pair<int,int> **neighborhood;
    int nb_neighbors=4;
public:
    VonNeumannNeighborhood(const int hauteur,const int largeur );
};
class VonNeumannNeighborhoodGeneralized: public NeighborhoodStrategy{
    std::pair<int,int> **neighborhood;
    unsigned int radius;
    unsigned int nb_neighbors;
public:
    VonNeumannNeighborhoodGeneralized(const int hauteur,const int largeur, unsigned int radius=1);

};
class MooreNeighborhood: public NeighborhoodStrategy{
    std::pair<int,int> **neighborhood;
    int nb_neighbors=8;
public:
    MooreNeighborhood(const int hauteur,const int largeur);
};

class MooreNeighborhoodGeneralized: public NeighborhoodStrategy{
    std::pair<int,int> **neighborhood;
    unsigned int radius;
    unsigned int nb_neighbors;
public:
    MooreNeighborhoodGeneralized(const int hauteur,const int largeur, unsigned int radius=1);
};

class ArbitraryNeighborhood: public NeighborhoodStrategy{
    std::pair<int,int> **neighborhood;
    unsigned int nb_neighbors;
public:
    ArbitraryNeighborhood(const int hauteur,const int largeur);
};

#endif //LO21_NEIGHBORHOODSTRATEGY_H
