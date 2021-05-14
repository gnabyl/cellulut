#ifndef LO21_SIMULATOR_H
#define LO21_SIMULATOR_H

#include "automata.h"


class Simulator {
private:
    const Automata &automata;
    size_t bufferSize;
    const Grid *startGrid = nullptr; // il faut ajouter un pointeur dans l'UML
    Grid **grids = nullptr;
    // Gridfactory gridFactory
    size_t gridIDcurrent=0; // il s'agit du rang

    //void build(size_t c);

    Simulator(const Simulator &s) = delete;

    Simulator &operator=(const Simulator &s) = delete;


public:
    Simulator(const Automata &a, size_t buf = 2);

    Simulator(const Automata &a, const Grid &startG, size_t buf = 2);

    ~Simulator();

    void setStartGrid(const Grid &g);

    void reset();

    void run(size_t nbSteps = 1);
    void next();
    void build(size_t id);
    unsigned int frequency; // vitesse de passage d'une génération à une autre

    // Important A voir s'il faudra l'implémenter

    //const Etat& dernier() const;
    //size_t getRangDernier() const;

    class Iterator {
        friend class Simulator;

    private:
        Simulator *sim = nullptr;
        int gridID = 0;

        Iterator(Simulator *s);

    public:
        Iterator();

        bool isDone() const;

        void previousGrid();

        void nextGrid();

        Grid &current() const;

        //operator!=(): bool
    };

    Iterator getIterator();
};



#endif //LO21_SIMULATOR_H
