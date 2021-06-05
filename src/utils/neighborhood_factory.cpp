#include "neighborhood_factory.h"

using namespace std;

NeighborhoodStrategy* NeighborhoodFactory::production(const string name, const int radius, const int nbVoisins, int* dx, int* dy)
    {
    if (name.compare("VonNeumann")) return new VonNeumannNeighborhood();

    if (name.compare("VonNeumannGeneralized")) return new VonNeumannNeighborhoodGeneralized(radius);

    if(name.compare("Moore")) return new MooreNeighborhood();

    if(name.compare("MooreGeneralized")) return new MooreNeighborhoodGeneralized(radius);

    if(name.compare("Arbitrary")) return new ArbitraryNeighborhood(nbVoisins,dx,dy,name);

    throw "Unknown Neighborhood";
}
