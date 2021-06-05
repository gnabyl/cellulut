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
/**
 * @brief NeighborhoodStrategy classe abstraite permettant de déléguer les différents types de voisinages
 */
class NeighborhoodStrategy {
    /**
     * @brief name nom du voisinage
     */
    std::string name;
  public:
    /**
     * @brief NeighborhoodStrategy Constructeur de la classe NeighborhoodStrategy
     * @param na nom a donné au voisinage
     */
    NeighborhoodStrategy(std::string na): name(na) {}
    /**
     * @brief getNeighbors  méthode virtuelle dont le comportement est définies dans les classe filles
     * @param c cellule
     * @param g
     * @return Cell**
     */
    virtual Cell** getNeighbors(Cell* c, Grid* g) = 0;
    /**
     * @brief getNbNeighbors
     * @return
     */
    virtual int getNbNeighbors() const = 0 ;
    /**
     * @brief getName
     * @return
     */
    std::string getName() const  {
        return name;
    }
    //virtual int getRadius() const;
    //virtual int* getDx() const;
    //virtual int* getDy() const;
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
    virtual Cell** getNeighbors(Cell* c, Grid* g);
};

class VonNeumannNeighborhoodGeneralized: public NeighborhoodStrategy {
    Cell** neighbors;
    int radius;
    int nbNeighbors;
    std::string name = "Von Neumann Neighborhood Generalized";
  public:
    VonNeumannNeighborhoodGeneralized(int radius = 1);
    ~VonNeumannNeighborhoodGeneralized() {
        delete[] neighbors;
    }
    int getNbNeighbors() const {
        return nbNeighbors;
    }
    int getRadius() const {return radius;}
    virtual Cell** getNeighbors(Cell* c, Grid* g);
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
    virtual Cell** getNeighbors(Cell* c, Grid* g);
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
    int getRadius() const {return radius;}
    virtual Cell** getNeighbors(Cell* c, Grid* g);
};

class ArbitraryNeighborhood: public NeighborhoodStrategy {
    Cell** neighbors;
    int nbNeighbors;
    int* dx;
    int* dy;
  public:
    ArbitraryNeighborhood(int nbNeighbors, int* dx, int* dy, std::string na);
    ~ArbitraryNeighborhood() {
        delete[] neighbors;
    }
    int getNbNeighbors() const {
        return nbNeighbors;
    }
//    int* getDx(){return dx;}
//    int* getDy(){return dy;}
    virtual Cell** getNeighbors(Cell* c, Grid* g);
};

#endif //LO21_NEIGHBORHOODSTRATEGY_H
