//
// Created by Baptiste on 18/04/2021.
//

#ifndef LO21_SIMULATOR_H
#define LO21_SIMULATOR_H


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
    void next(); // important à voir si on utilise ou pas
    void build(size_t id);
    unsigned int frequency; // vitesse de passage d'une génération à une autre

    // Important A voir s'il faudra l'implémenter

    //const Etat& dernier() const;
    //size_t getRangDernier() const;
    //void reset();

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
}

    // Important besoin d'un const iterator ou pas ?
    // Je pense que non puisque l'on peut modifier notre grille lorsque l'on fait un parcourt
    /*
    class ConstIterator
    {
        friend class Simulateur;

    private:
        const Simulateur* sim = nullptr;
        int i=0;
        ConstIterator(const Simulateur* s);

    public:
        ConstIterator();
        bool isDone() const;
        void next();
        const Etat& current() const;
    };

    ConstIterator getIterator() const;
    ConstIterator getConstIterator() const;
};
*/

#endif //LO21_SIMULATOR_H
