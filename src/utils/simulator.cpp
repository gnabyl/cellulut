#include "simulator.h"

BufferException::BufferException(std::string s) : info(s){}

void Simulator::allocateBuffer() {
    if (grids != nullptr) {
        for(int i = 0; i < bufferSize; i++) {
            if (grids[i] != nullptr) {
                delete grids[i];
                grids[i] = nullptr;
            }
        }
        delete[] grids;
        grids = nullptr;
    }
    grids = new Grid*[bufferSize];
    for(int i = 0; i < bufferSize; i++) grids[i] = nullptr;
}

void Simulator::setAutomata(Automata *automata) {
    this->automata = automata;
}

Automata* Simulator::getAutomata() const {
    return this->automata;
}

Simulator::Simulator(Automata* a, int buf): automata(a), bufferSize(buf), maxID(0) {
    /*grids = new Grid*[bufferSize];
    for(int i=0; i<bufferSize; i++) grids[i]=nullptr;*/
    allocateBuffer();
}

Simulator::Simulator(Automata* a, Grid& startG, int buf): automata(a),  bufferSize(buf), startGrid(&startG), maxID(0){
    /*grids = new Grid*[bufferSize];
    for(int i=0; i<bufferSize; i++) grids[i]=nullptr;*/
    allocateBuffer();
    grids[0] = new Grid(startG);
}

void Simulator::setStartGrid(Grid *g) {
    if (startGrid != nullptr) {
        delete startGrid;
        startGrid = nullptr;
    }

    startGrid = g;

    // reset(); // Important à revoir
    reset(); // build(0) va dans ce cas créer une nouvel état
}
// important j'ai laissé comme cela (séparation run et next) à voir si c'est bien ou pas
void Simulator::run(int nbSteps) {
    for(int i = 0; i < nbSteps; i++) next();
}

void Simulator::next() {
    if(startGrid == nullptr)
        return;
    try {
        currentGridID++; //important à regarder
        if(currentGridID > maxID) maxID = currentGridID;

        if (grids[currentGridID % bufferSize]) {
            delete grids[currentGridID % bufferSize];
            grids[currentGridID % bufferSize] = nullptr;
        }
        grids[currentGridID % bufferSize] = automata->applyTransition(grids[(currentGridID - 1) % bufferSize]);
    }  catch (TransitionException e) {
        currentGridID --;
        throw;
    }
}
/*
const Etat& Simulateur::dernier() const
{
    return *etats[rang%nbMaxEtats];
}

int Simulateur::getRangDernier() const
{
    return rang;
}

*/
void Simulator::reset() { // important je ne l'ai pas mis const car pour moi cette fonction correspond à la fonction reset du TD
    if (startGrid == nullptr) throw "start grid is not defined";
    currentGridID = 0;
    maxID = 0;
    if (grids[0]) {
        delete grids[0];
        grids[0] = nullptr;
    }
    grids[0] = new Grid(*startGrid);
}
/*
void Simulator::build(int ID)
{
    if (ID>=bufferSize) throw AutomateException("issue buffer size outrange");
    if(grids[ID] == nullptr) grids[ID] = new Grid;
}*/

Simulator::~Simulator() {
    for(int i = 0; i < bufferSize; i++) {
        delete grids[i];
        grids[i] = nullptr;
    }
    delete[] grids;
    grids = nullptr;
}


Simulator::Iterator Simulator::getIterator() {
    return Iterator(this);
}

int Simulator::getBufferSize() const{
    return bufferSize;
}

void Simulator::setBufferSize(int size){
    bufferSize = size;
}

int Simulator::getCurrentGridID() const {
    return this->currentGridID;
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

Simulator::Iterator::Iterator() {

}

Simulator::Iterator::Iterator(Simulator* s): sim(s), gridID(s->currentGridID % s->getBufferSize()) { // important regarder l'histoire de rang

}

bool Simulator::Iterator::isDone() const {
    return sim == nullptr || gridID == -1 || (sim->currentGridID <= sim->maxID-sim->bufferSize);
    //return sim == nullptr || gridID == -1 || sim->currentGridID % (sim->getBufferSize()) != gridID ; // important
}

void Simulator::Iterator::nextGrid() {
    //if(isDone()) throw "Issue : next on a finite iterator!";
    gridID = (gridID+1) % sim->getBufferSize();
}

void Simulator::Iterator::previousGrid() {
    if(isDone()) throw "Issue : previous on a finite iteraror !";
    sim->currentGridID--;
    gridID = (gridID-1 + sim->getBufferSize()) % (sim->getBufferSize());
}

Grid* Simulator::Iterator::current() const {
    //if(isDone()) throw "Issue : current on finite iteraror !";
    return sim->grids[gridID];
}
