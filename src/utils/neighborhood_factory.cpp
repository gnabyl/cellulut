#include "neighborhood_factory.h"

using namespace std;
NeighborhoodStrategy* NeighborhoodFactory::production(const string neighborhoodName) const {
    if(neighborhoodName == "Moore Neighborhood") return new MooreNeighborhood;
    if(neighborhoodName == "Von Neumann Neighborhood") return new VonNeumannNeighborhood;
    if(neighborhoodName == "Moore Neighborhood Generalized") return new MooreNeighborhoodGeneralized(1);
    if(neighborhoodName == "Von Neumann Neighborhood Generalized") return new MooreNeighborhoodGeneralized(1);
    throw "Unknown Neighborhood";
}

NeighborhoodStrategy* NeighborhoodFactory::production(const string name, const int radius) const {
    if (name.compare("Von Neumann Neighborhood Generalized")) return new VonNeumannNeighborhoodGeneralized(radius);
    if (name.compare("Moore Neighborhood Generalized")) return new MooreNeighborhoodGeneralized(radius);

    throw "Unknown Neighborhood";
}

NeighborhoodStrategy* NeighborhoodFactory::production(const string name, const int nbVoisins, int* dx, int* dy) const {
    return new ArbitraryNeighborhood(nbVoisins, dx, dy, name);
}
