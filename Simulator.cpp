//
// Created by Baptiste on 18/04/2021.
//

#include "Simulator.h"


///-------------------------------------------------------------------
/// Classe Simulator
///-------------------------------------------------------------------


Simulator::Simulator(const Automate& a, size_t buf):automata(a),bufferSize(buf)
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
}
// important j'ai laissé comme cela (séparation run et next) à voir si c'est bien ou pas
void Simulator::run(size_t nbSteps)
{
    for(size_t i=0; i<nbSteps; i++) next();
}

void Simulator::next()
{
    if(startGrid == nullptr) throw AutomateException("grille de départ indefinie");
    //rang++; important à regarder
    //build(rang%nbMaxEtats); important à regarder
    automata.applyTransition(/* *grids[(rang-1)%bufferSize],*grids[rang%bufferSize]*/);
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
Simulator::~Simulator()
{
    for(size_t i=0; i<bufferSize; i++) delete grids[i];
    delete[] grids;
}
/*
void Simulateur::build(size_t c)
{
    if (c>=nbMaxEtats) throw AutomateException("erreur taille buffer");
    if(grids[c] == nullptr) grids[c] = new Etat;
}
*/

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

Simulator::Iterator::Iterator(Simulator* s):sim(s),gridID(s->rang) // important regarder l'histoire de rang
{

}

bool Simulator::Iterator::isDone() const
{
    return sim == nullptr || gridID==-1 || gridID == sim->rang-sim->bufferSize; // important
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






