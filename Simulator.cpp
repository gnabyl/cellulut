#include <cstddef>
#include "Simulator.h"

void allocateBuffer() {
    if (grids != nullptr) {
        for(size_t i=0; i<bufferSize; i++) {
            if (grids[i]!= nullptr)
            {
                delete grids[i];
                grids[i] = nullptr;
            }
        }
        delete[] grids;
    }
    grids = new Grid*[bufferSize];
    for(size_t i=0; i<bufferSize; i++) grids[i]=new Grid;
}

Simulator::Simulator(const Automata& a, size_t buf):automata(a),bufferSize(buf)
{
    /*grids = new Grid*[bufferSize];
    for(size_t i=0; i<bufferSize; i++) grids[i]=nullptr;*/
    allocateBuffer();
}

Simulator::Simulator(const Automata& a, const Grid& startG, size_t buf):automata(a),startGrid(&startG),bufferSize(buf)
{
    /*grids = new Grid*[bufferSize];
    for(size_t i=0; i<bufferSize; i++) grids[i]=nullptr;*/
    allocateBuffer();
    //grids[0]=new Grid(startG);
    *grids[0]=startG;
}

void Simulator::setStartGrid(const Grid& g)
{
    startGrid = &g;
    // reset(); // Important à revoir
    reset(); // build(0) va dans ce cas créer une nouvel état
}
// important j'ai laissé comme cela (séparation run et next) à voir si c'est bien ou pas
void Simulator::run(size_t nbSteps)
{
    for(size_t i=0; i<nbSteps; i++) next();
}

void Simulator::next()
{
    if(startGrid == nullptr) throw AutomateException("start grid is not defined");
    gridIDcurrent++; //important à regarder

    grids[gridIDcurrent%bufferSize] = automata.applyTransition(grids[(gridIDcurrent-1)%bufferSize]);



    //build(gridIDcurrent%bufferSize);
    //automata.applyTransition(grids[(gridIDcurrent-1)%bufferSize],*grids[gridIDcurrent%bufferSize]); // important rang
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

*/
void Simulator::reset() { // important je ne l'ai pas mis const car pour moi cette fonction correspond à la fonction reset du TD
    if (startGrid == nullptr) throw AutomateException("start grid is not defined");
    gridIDcurrent = 0;
    /*build(0);*/
    *grids[0] = *startGrid;
}
/*
void Simulator::build(size_t ID)
{
    if (ID>=bufferSize) throw AutomateException("issue buffer size outrange");
    if(grids[ID] == nullptr) grids[ID] = new Grid;
}*/

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
    if(isDone()) throw AutomateException("Issue : next on a finite iterator!");
    gridID++;
}

void Simulator::Iterator::previousGrid()
{
    if(isDone()) throw AutomateException("Issue : previous on a finite iteraror !");
    gridID--;
}

Grid& Simulator::Iterator::getCurrentGrid() const
{
    if(isDone()) throw AutomateException("Issue : current on finite iteraror !");
    return *sim->grids[gridID%sim->bufferSize];
}
