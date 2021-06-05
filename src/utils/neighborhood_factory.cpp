#include "neighborhood_factory.h"

using namespace std;

//NeighborhoodStrategy* NeighborhoodFactory::production(const string name, const int radius=1, const int nbVoisins=0, const int* dx=nullptr, const int* dy=nullptr)
//{
//    if (name.compare("VonNeumann")) return new VonNeumannNeighborhood();

//    if (name.compare("VonNeumannGeneralized")) return new VonNeumannNeighborhoodGeneralized(radius);

//    if(name.compare("Moore")) return new MooreNeighborhood();

//    if(name.compare("MooreGeneralized")) return new MooreNeighborhoodGeneralized(radius);

//    if(name.compare("Arbitrary")) return new ArbitraryNeighborhood(nbVoisins,dx,dy);

//    throw "Unknown Neighborhood";
//}
