#include "neighborhood_factory.h"

using namespace std;
NeighborhoodStrategy* NeighborhoodFactory::production(const string name){
    if (name.compare("VonNeumann")) return new VonNeumannNeighborhood();
    if(name.compare("Moore")) return new MooreNeighborhood();
    throw "Unknown Neighborhood";
}
NeighborhoodStrategy* NeighborhoodFactory::production(const string name, const int radius)
    {
    if (name.compare("VonNeumannGeneralized")) return new VonNeumannNeighborhoodGeneralized(radius);
    if(name.compare("MooreGeneralized")) return new MooreNeighborhoodGeneralized(radius);

    throw "Unknown Neighborhood";
}

NeighborhoodStrategy* NeighborhoodFactory::production(const string name, const int nbVoisins, int* dx, int* dy){
    return new ArbitraryNeighborhood(nbVoisins,dx,dy,name);
}
