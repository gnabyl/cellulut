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
