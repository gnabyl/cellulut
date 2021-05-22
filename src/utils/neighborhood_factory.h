#ifndef NEIGHBORHOOD_FACTORY_H
#define NEIGHBORHOOD_FACTORY_H
#include "neighborhood_strategy.h"
#include <string>

using namespace std;

class NeighborhoodFactory {

public:
    ~NeighborhoodFactory(){};
    NeighborhoodStrategy* production(const string name, const int radius=1, const int nbVoisins=0);

};

#endif // NEIGHBORHOOD_FACTORY_H
