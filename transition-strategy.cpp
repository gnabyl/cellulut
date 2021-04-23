#include "transition-strategy.h"

void TransitionContext::setStrategy(TransitionStrategy* s){
	if(strategy != nullptr)
		delete strategy;
	strategy = s;
}

Cell TotalisticTransition::calcNextCell(const Cell c, const Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates) const{
	/*Find a way to implement any totalistic transition. Remember that it only takes into account the sum of the neighbor's current states' IDs.*/
}

/*
Caractéristiques :
- Règle totalistique
- Taille du voisinage : 8 -> moyen de le vérifier ? On rajoute un argument ?
- Nombre d'états possibles : 2 -> on rajoute un argument.
Suppositions :
- Les id des états sont forcément 0 ou 1. On pourra gérer ça avec des modulo ensuite si besoin.
*/
Cell GOLTransition::calcNextCell(const Cell c, const Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates) const override{
	if(neighborSize != 8)
		throw TransitionException("La taille du voisinage choisi est incohérente avec la fonction de transition utilisée : Game of Life exige un voisinage de 8 cellules.\n");
	if(nbStates != 2)
		throw TransitionException("Le nombre d'états de l'automate est incohérent avec la règle de transition choisie : Game of Life ne fonctionne qu'avec 2 états possibles.\n");
	int sum = 0;
	for(int i=0; i<neighborSize; i++){
		sum += (availableStates[0]->id == neighbors[i]->state.id) ? 0 : 1;
	}
	if(c.state == 0 && sum == 3)
		return new Cell(availableStates[1]);
	if(c.state == 1 && (sum == 2 || sum == 3))
		return new Cell(availableStates[1]);
	if(c.state == 1 && (sum<2 || sum>3))
		return new Cell(availableStates[0]);
	else return new Cell(c.state);
}