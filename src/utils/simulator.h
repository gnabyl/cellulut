#ifndef LO21_SIMULATOR_H
#define LO21_SIMULATOR_H

#include "automata.h"
#include "grid.h"
#include "grid_factory.h"

/**
 * @brief The BufferException class gestionnaire d'erreurs lié au buffer
 */
class BufferException{
    /**
     * @brief info  chaine de caractères contenant des informations sur l'erreur
     */
    std::string info;
public:
    /**
     * @brief BufferException   constructeur de la classe BufferException
     * @param s message d'erreur
     */
    BufferException(std::string s):info(s){};
    std::string getInfo() const{return info;}
};

class Simulator {
  public:
    static GridFactory& getGridFactory() {
        static GridFactory gridFactory;
        return gridFactory;
    }
  private:
    Automata* automata;
    int bufferSize;
    Grid* startGrid = nullptr;
    Grid** grids = nullptr;
    // Gridfactory gridFactory
    int currentGridID = 0; // il s'agit du rang
    int maxID;

    //void build(int c);

    Simulator(const Simulator& s) = delete;

    Simulator& operator=(const Simulator& s) = delete;


  public:
    Simulator(Automata* a, int buf = 2);

    Simulator(Automata* a, Grid& startG, int buf = 2);

    ~Simulator();

    void allocateBuffer();

    void setStartGrid(Grid* g);

    void reset();

    void run(int nbSteps = 1);
    void next();
    void build(int id);
    unsigned int frequency; // vitesse de passage d'une génération à une autre



    void setAutomata(Automata* automata);
    void setBufferSize(int);
    Automata* getAutomata() const;
    int getBufferSize() const;

    int getCurrentGridID() const;

    class Iterator {
        friend class Simulator;

      private:
        Simulator* sim = nullptr;
        int gridID = 0;

        Iterator(Simulator* s);

      public:
        Iterator();

        bool isDone() const;

        void previousGrid();

        void nextGrid();

        Grid* current() const;

        //operator!=(): bool
    };

    Iterator getIterator();
};



#endif //LO21_SIMULATOR_H
