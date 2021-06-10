#ifndef TRANSITION_FACTORY_H
#define TRANSITION_FACTORY_H
#include "transition_strategy.h"
#include <string>

using namespace std;

class TransitionFactory {

public:
    TransitionStrategy* production(const string name) const;

};
#endif // TRANSITION_FACTORY_H
