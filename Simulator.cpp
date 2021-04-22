//
// Created by Baptiste on 18/04/2021.
//

#include <cstddef>
#include "Simulator.h"


///-------------------------------------------------------------------
/// Classe Simulator
///-------------------------------------------------------------------


Simulator::Simulator(const Automata& a, size_t buf):automata(a),bufferSize(buf)
{
    grids = new Grid*[bufferSize];
    for(size_t i=0; i<bufferSize; i++) grids[i]=nullptr;
}

Simulator::Simulator(const Automata& a, const Grid& startG, size_t buf):automata(a),startGrid(&startG),bufferSize(buf)
{
    grids = new Grid*[bufferSize];
    for(size_t i=0; i<bufferSize; i++) grids[i]=nullptr;
    grids[0]=new Grid(startG);
}

void Simulator::setStartGrid(const Grid& g)
{
    startGrid = &g;
    // reset(); // Important à revoir
    getStartGrid(); // build(0) va dans ce cas créer une nouvel état
}
// important j'ai laissé comme cela (séparation run et next) à voir si c'est bien ou pas
void Simulator::run(size_t nbSteps)
{
    for(size_t i=0; i<nbSteps; i++) next();
}

void Simulator::next()
{
    if(startGrid == nullptr) throw AutomateException("grille de départ indefinie");
    gridIDcurrent++; //important à regarder
    build(gridIDcurrent%bufferSize); //important à REVOIR !
    automata.applyTransition(grids[(gridIDcurrent-1)%bufferSize],*grids[gridIDcurrent%bufferSize]); // important rang
}
/*
const Etat& Simulateur::dernier() const
{
    return *etats[rang%nbMaxEtats];
}

size_t Simulateur::getRangDernier() const
{
    return rang;
}

void Simulateur::reset()
{
    if(depart == nullptr) throw AutomateException("etat depart indefini");
    rang=0;
    build(0);
    *etats[0]=*depart;
}
*/

void Simulator::getStartGrid() { // important je ne l'ai pas mis const car pour moi cette fonction correspond à la fonction reset du TD
    if (startGrid == nullptr) throw AutomateException("start grid is not defined");
    gridIDcurrent = 0;
    build(0);
    *grids[0] = *startGrid;
}
void Simulator::build(size_t ID)
{
    if (ID>=bufferSize) throw AutomateException("issue buffer size outrange");
    if(grids[ID] == nullptr) grids[ID] = new Grid;
}

Simulator::~Simulator()
{
    for(size_t i=0; i<bufferSize; i++) delete grids[i];
    delete[] grids;
}


Simulator::Iterator Simulator::getIterator()
{
    return Iterator(this);
}
/*
Simulateur::ConstIterator Simulateur::getIterator() const
{
    return ConstIterator(this);
}

Simulateur::ConstIterator Simulateur::getConstIterator() const
{
    return ConstIterator(this);
}

*/

///-------------------------------------------------------------------
/// Classe Simulator::Iterator
///-------------------------------------------------------------------

Simulator::Iterator::Iterator()
{

}

Simulator::Iterator::Iterator(Simulator* s):sim(s),gridID(s->gridIDcurrent) // important regarder l'histoire de rang
{

}

bool Simulator::Iterator::isDone() const
{
    return sim == nullptr || gridID==-1 || gridID == sim->gridIDcurrent-sim->bufferSize; // important
}

void Simulator::Iterator::nextGrid()
{
    if(isDone()) throw AutomateException("Erreur: next sur un iteraror fini!");
    gridID++;
}

void Simulator::Iterator::previousGrid()
{
    if(isDone()) throw AutomateException("Erreur: previous sur un iteraror fini!");
    gridID--;
}

Grid& Simulator::Iterator::getCurrentGrid() const
{
    if(isDone()) throw AutomateException("Erreur: current sur un iteraror fini!");
    return *sim->grids[gridID%sim->bufferSize];
}






