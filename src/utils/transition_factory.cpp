#include "transition_factory.h"

using namespace std;

TransitionStrategy* TransitionFactory::production(const string name)
{
    if (name.compare("GOL")) return new GOLTransition();

    if (name.compare("BB")) return new BBTransition();
/*
    if(name.compare("DG")) return new DGTransition();

    if(name.compare("LL")) return new LLTransition();

    if(name.compare("LA")) return new LATransition();
*/
    throw "Unknown Transition";
}
