#include "transition_strategy.h"

/*
FONCTION DE TRANSITION DU JEU DE LA VIE
Caractéristiques :
- Règle totalistique
- Taille du voisinage : 8
- Nombre d'états possibles : 2
Suppositions :
- Les id des états sont forcément 0 ou 1. On pourra gérer ça avec des modulo ensuite si besoin.
*/
Cell* GOLTransition::calcNextCell(Cell* c, Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates) const {
    if(neighborSize != 8)
        throw TransitionException("La taille du voisinage choisi est incohérente avec la fonction de transition utilisée : Game of Life exige un voisinage de 8 cellules.\n");
    if(nbStates != 2)
        throw TransitionException("Le nombre d'états de l'automate est incohérent avec la règle de transition choisie : Game of Life ne fonctionne qu'avec 2 états possibles.\n");
    int sum = 0;
    for(int i = 0; i < neighborSize; i++) {
        if(availableStates[1]->getId() == neighbors[i]->getState()->getId()) sum += 1;
    }
    if(c->getState()->getId() == availableStates[0]->getId() && sum == 3)
        return new Cell(availableStates[1], c->getX(), c->getY());
    if(c->getState()->getId() == availableStates[1]->getId() && (sum == 2 || sum == 3))
        return new Cell(availableStates[1], c->getX(), c->getY());
    if(c->getState()->getId() == availableStates[1]->getId() && (sum < 2 || sum > 3))
        return new Cell(availableStates[0], c->getX(), c->getY());
    else return new Cell(c->getState(), c->getX(), c->getY());
}

/*
FONCTION DE TRANSITION DE BRIAN'S BRAIN
Caractéristiques :
- Règle totalistique
- Taille du voisinage : 8
- Nombre d'états possibles : 3
Suppositions :
- Les id des états sont forcément 0 (repos), 1 (réfractaire) ou 2 (excitée).
*/
Cell* BBTransition::calcNextCell(Cell* c, Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates) const {
    if(neighborSize != 8)
        throw TransitionException("La taille du voisinage choisi est incohérente avec la fonction de transition utilisée : Brian's Brain exige un voisinage de 8 cellules.\n");
    if(nbStates != 3)
        throw TransitionException("Le nombre d'états de l'automate est incohérent avec la règle de transition choisie : Brian's Brain ne fonctionne qu'avec 3 états possibles.\n");
    //Toute cellule excitée devient réfractaire.
    if(c->getState()->getId() == availableStates[2]->getId()) {
        return new Cell(availableStates[1], c->getX(), c->getY());
    }
    //Toute cellule réfractaire devient au repos.
    if(c->getState()->getId() == availableStates[1]->getId()) {
        return new Cell(availableStates[0], c->getX(), c->getY());
    }
    //Pour une cellule au repos, on s'intéresse au nombre de cellules excitées dans le voisinage.
    int sum = 0;
    for(int i = 0; i < neighborSize; i++) {
        if(availableStates[2]->getId() == neighbors[i]->getState()->getId()) sum += 1;
    }
    //Toute cellule au repos ayant exactement 2 voisinges excitées devient excitée.
    if(c->getState()->getId() == availableStates[0]->getId() && sum == 2) {
        return new Cell(availableStates[2], c->getX(), c->getY());
    }
    return new Cell(*c);
}

/************************************************AJOUT DES AUTRES REGLES DE TRANSITION***************************************/


/*
FONCTION DE TRANSITION DE L'AUTOMATE CIRCULAIRE DE DAVID GRIFFEATH
- Règle totalistique
- Taille du voisinage : 8 (MOORE)
- Nombre d'états possibles : 4
Suppositions :
- Les id des états sont forcément 0 (jaune), 1 (orange clair),2 (orange foncé), 3 (rouge)
*/

Cell DGTransition::calcNextCell(const Cell c, const Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates) const{
    if(neighborSize!=8)
        throw TransitionException("La taille du voisinage choisi est incohérente avec la fonction de transition utilisée : Brian's Brain exige un voisinage de 8 cellules.\n");
    if(nbStates!=2)
        throw TransitionException("Le nombre d'états de l'automate est incohérent avec la règle de transition choisie : Brian's Brain ne fonctionne qu'avec 3 états possibles.\n");

    // determiner la couleur suivante par rapport à notre cellule dans le cyle des quatres couleurs
    j = 0 // j est l'indice de la couleur de la cellule c
   while(c.getState().getid() != availableStates[j%4]->getId())
    {
        j++
    }
   // nous calculons le nombre de voisins ayant la couleur d'indice j+1
    int sum = 0;
    for(unsigned int i=0;i<neighborSize;i++){
        if(availableStates[(j+1)%4]->getId() == neighbors[i]->state.getId()) sum+=1;
    }
    // si la couleur d'indice j+1 est présente dans au moins 3 cellules voisines, la cellule c prend la couleur d'indice j+1
    if(sum>=3)
        return new Cell(availableStates[(j+1)%4],c.getX(),c.getY());
}

/*
FONCTION DE TRANSITION DE LANGTON'S LOOP
- Règle totalistique
- Taille du voisinage : 4 (VON NEUMANN)
- Nombre d'états possibles : 8
*/

#include <map>


Cell LLTransition::calcNextCell(const Cell c, const Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates) const{

    // dictionnaire de l'ensemble des règles
    std::map <int, int> langtonRules =
    {

        {00000,0},
        {00001,2},
        {00002,0},
        {00003,0},
        {00005,0},
        {00006,3},
        {00007,1},
        {00011,2},
        {00012,2},
        {00013,2},
        {00021,2},
        {00022,0},
        {00023,0},
        {00026,2},
        {00027,2},
        {00032,0},
        {00052,5},
        {00062,2},
        {00072,2},
        {00102,2},
        {00112,0},
        {00202,0},
        {00203,0},
        {00205,0},
        {00212,5},
        {00222,0},
        {00232,2},
        {00522,2},
        {01232,1},
        {01242,1},
        {01252,5},
        {01262,1},
        {01272,1},
        {01275,1},
        {01422,1},
        {01432,1},
        {01442,1},
        {01472,1},
        {01625,1},
        {01722,1},
        {01725,5},
        {01752,1},
        {01762,1},
        {01772,1},
        {02527,1},
        {10001,1},
        {10006,1},
        {10007,7},
        {10011,1},
        {10012,1},
        {10021,1},
        {10024,4},
        {10027,7},
        {10051,1},
        {10101,1},
        {10111,1},
        {10124,4},
        {10127,7},
        {10202,6},
        {10212,1},
        {10221,1},
        {10224,4},
        {10226,3},
        {10227,7},
        {10232,7},
        {10242,4},
        {10262,6},
        {10264,4},
        {10267,7},
        {10271,0},
        {10272,7},
        {10542,7},
        {11112,1},
        {11122,1},
        {11124,4},
        {11125,1},
        {11126,1},
        {11127,7},
        {11152,2},
        {11212,1},
        {11222,1},
        {11224,4},
        {11225,1},
        {11227,7},
        {11232,1},
        {11242,4},
        {11262,1},
        {11272,7},
        {11322,1},
        {12224,4},
        {12227,7},
        {12243,4},
        {12254,7},
        {12324,4},
        {12327,7},
        {12425,5},
        {12426,7},
        {12527,5},
        {20001,2},
        {20002,2},
        {20004,2},
        {20007,1},
        {20012,2},
        {20015,2},
        {20021,2},
        {20022,2},
        {20023,2},
        {20024,2},
        {20025,0},
        {20026,2},
        {20027,2},
        {20032,6},
        {20042,3},
        {20051,7},
        {20052,2},
        {20057,5},
        {20072,2},
        {20102,2},
        {20112,2},
        {20122,2},
        {20142,2},
        {20172,2},
        {20202,2},
        {20203,2},
        {20205,2},
        {20207,3},
        {20212,2},
        {20215,2},
        {20221,2},
        {20222,2},
        {20227,2},
        {20232,1},
        {20242,2},
        {20245,2},
        {20252,0},
        {20255,2},
        {20262,2},
        {20272,2},
        {20312,2},
        {20321,6},
        {20322,6},
        {20342,2},
        {20422,2},
        {20512,2},
        {20521,2},
        {20522,2},
        {20552,1},
        {20572,5},
        {20622,2},
        {20672,2},
        {20712,2},
        {20722,2},
        {20742,2},
        {20772,2},
        {21122,2},
        {21126,1},
        {21222,2},
        {21224,2},
        {21226,2},
        {21227,2},
        {21422,2},
        {21522,2},
        {21622,2},
        {21722,2},
        {22227,2},
        {22244,2},
        {22246,2},
        {22276,2},
        {22277,2},
        {30001,3},
        {30002,2},
        {30004,1},
        {30007,6},
        {30012,3},
        {30042,1},
        {30062,2},
        {30102,1},
        {30122,0},
        {30251,1},
        {40112,0},
        {40122,0},
        {40125,0},
        {40212,0},
        {40222,1},
        {40232,6},
        {40252,0},
        {40322,1},
        {50002,2},
        {50021,5},
        {50022,5},
        {50023,2},
        {50027,2},
        {50052,0},
        {50202,2},
        {50212,2},
        {50215,2},
        {50222,0},
        {50224,4},
        {50272,2},
        {51212,2},
        {51222,0},
        {51242,2},
        {51272,2},
        {60001,1},
        {60002,1},
        {60212,0},
        {61212,5},
        {61213,1},
        {61222,5},
        {70007,7},
        {70112,0},
        {70122,0},
        {70125,0},
        {70212,0},
        {70222,1},
        {70225,1},
        {70232,1},
        {70252,5},
        {70272,0},
    };

    for (int i = 0; i < neighborSize; ++i) { // il faut tester chaque combinaison possible
        // on convertit la cellule et le voisinage en clé (nombre de 5 chiffres)
        key = c*10000+neighbors[i%4]*1000+neighbors[(i+1)%4]*100+ neighbors[(i+2)%4]*10 + neighbors[(i+3)%4];
        // on vérifie si la clé et donc la règle existe : si oui on modifie.
        if(langtonRules.find(key)!=langtonRules.end())
            return new Cell(availableStates[langtonRules[key]],c.getX(),c.getY())
        }
    }






/* ============================================ LANGTON ANTS NON FONCTIONNELLE ================================================== */

/*
FONCTION DE TRANSITION DE LANGTON ANT
- Depart : il faut pouvoir définir l'orientation de départ de la fourmi (de la 1ere celulle)
 1) rajouter un attribut orientation à la classe cellule
 2) modifier l'orientation de la cellule sur l'interface graphique
 http://www.langtonant.com/
 https://fr.wikipedia.org/wiki/Fourmi_de_Langton
 http://www.dim.uchile.cl/~anmoreir/oficial/langton_dam.pdf
 https://www.researchgate.net/profile/Majid-Vafaei-Jahan/publication/268289802_From_Complexity_to_Random_Behaviors_Generate_Random_Numbers_by_Confusion_in_Cellular_Automata_State%27s/links/551396f60cf283ee08348aed/From-Complexity-to-Random-Behaviors-Generate-Random-Numbers-by-Confusion-in-Cellular-Automata-States.pdf

 Il est également possible de définir la fourmi de Langton comme un automate cellulaire où la plupart des cases de la grille sont blanches ou noires et
 où la case de la fourmi peut prendre huit états différents, codant à la fois sa couleur et la direction de la fourmi.
-> en effet on a pour chacune des 2 couleurs 4 directions possibles suivant la direction / orientation de base de la cellule étudiée
 - Règle totalistique
- Taille du voisinage : 8 (von neumann)
- Nombre d'états possibles : 2 (noir ou blanc)
*/

/*
 * j'ai mis ceci car pour pouvoir intancier cette algorithme il faudra pour moi moi modifier cellulestate en rajoutant l'enum direction
 *
 * cellstate.h
 *
 *
#include <QColor>
#include <string>

enum color {blue, red, yellow, pink, cyan, green, orange, purple};
enum direction {up, down, left, right};

// https://en.cppreference.com/w/cpp/language/enum

class CellState {
  public:
    void setId(int i);
    void setLabel(std::string s);
    void setColor(QColor c);

    //modif
    void setDirection(direction d);

    int getId() const;

    // modif
    direction getDirection() const;

    QColor getColor() const;
    std::string getLabel() const;

    // modifier ici le constructeur

    CellState(int x, std::string l, QColor c,direction d): id(x), label(l), col(c), dir(d) {}

  private:
    int id;
    std::string label;
    QColor col;
    direction dir;
};
*/

// je ne me sers pas actuellement du voisinage
Cell LATransition::calcNextCell(const Cell c, const Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates) const{
    /*
    // s'assurer que #include "cellstate.h" est bien inclue
    map<Direction,int> list_direction
    {
        {up, c.getX() - 1},
        {down, c.getX() + 1},
        {left, c.getY() - 1},
        {right, c.getY() + 1},
    }
     */
    // if c is  white -> move 90° right
    if (c.getState().getId() == availableStates[0]->getId()){

        // on passe la couleur à blanc
        c.getState().getId() == availableStates[0]->getId();

        if(c.getState().getDirection()==up)
            c.getState().setDirection(right);
            c.setY(c.getY() + 1);

        if(c.getState().getDirection()==right)
            c.getState().setDirection(down);
            c.setX(c.getX() + 1);

        if(c.getState().getDirection()==down)
            c.getState().setDirection(left);
            c.setY(c.getY() - 1);

        if(c.getState().getDirection()==left)
            c.getState().setDirection(up);
            c.setX(c.getX() - 1);
    }
    else // la cellule est noir move 90° left
    {
        c.getState().getId() == availableStates[0]->getId();

        if(c.getState().getDirection()==up)
            c.getState().setDirection(left);
            c.setY(c.getY() - 1);


        if(c.getState().getDirection()==right)
            c.getState().setDirection(up);
            c.setX(c.getX() - 1);

        if(c.getState().getDirection()==down)
            c.getState().setDirection(right);
            c.setY(c.getY() + 1);

        if(c.getState().getDirection()==left)
            c.getState().setDirection(down);
            c.setX(c.getX() + 1);
        }
    }

}
