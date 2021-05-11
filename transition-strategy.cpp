#include "transition-strategy.h"

Cell TotalisticTransition::calcNextCell(const Cell c, const Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates) const{
	int sum = 0;
	for(int i=0; i<neighborSize; i++){
		int j=0;
		while(availableStates[j]!=neighbors[i]->state.id) j++;
		sum += j;
	}
	int newState = 0;
	for(int i=0; i<neighborSize*(nbStates-1); i++)
		if(result[i]==sum)
			newState = i;//Remplacer par un while.
	Cell* c = new Cell(/*Initialiser avec l'état obtenu dans availableStates[newState]*/);
	return c;
}

/*
FONCTION DE TRANSITION DU JEU DE LA VIE
Caractéristiques :
- Règle totalistique
- Taille du voisinage : 8
- Nombre d'états possibles : 2
Suppositions :
- Les id des états sont forcément 0 ou 1. On pourra gérer ça avec des modulo ensuite si besoin.
*/
Cell GOLTransition::calcNextCell(const Cell c, const Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates) const{
	if(neighborSize != 8)
		throw TransitionException("La taille du voisinage choisi est incohérente avec la fonction de transition utilisée : Game of Life exige un voisinage de 8 cellules.\n");
	if(nbStates != 2)
		throw TransitionException("Le nombre d'états de l'automate est incohérent avec la règle de transition choisie : Game of Life ne fonctionne qu'avec 2 états possibles.\n");
	int sum = 0;
	for(int i=0; i<neighborSize; i++){
		sum += (availableStates[0]->id == neighbors[i]->state.id) ? 0 : 1;
	}
	if(c.State.getid() == availableStates[0]->id && sum == 3)
		return new Cell(availableStates[1]);
	if(c.State.getid() == availableStates[1]->id && (sum == 2 || sum == 3))
		return new Cell(availableStates[1]);
	if(c.State.getid() == 1=availableStates[1]->id && (sum<2 || sum>3))
		return new Cell(availableStates[0]);
	else return new Cell(c.State);
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

Cell BBTransition::calcNextCell(const Cell c, const Cell** neighbors, int neighborSize, CellState** availableStates, int nbStates) const{
	if(neighborSize!=8)
		throw TransitionException("La taille du voisinage choisi est incohérente avec la fonction de transition utilisée : Brian's Brain exige un voisinage de 8 cellules.\n");
	if(nbStates!=2)
		throw TransitionException("Le nombre d'états de l'automate est incohérent avec la règle de transition choisie : Brian's Brain ne fonctionne qu'avec 3 états possibles.\n");
	//Toute cellule excitée devient réfractaire.
	if(c.State.getid()==availableStates[2]->id)
		return new Cell(availableStates[1]);
	//Toute cellule réfractaire devient au repos.
	if(c.State.getid()==availableStates[1]->id)
		return new Cell(availableStates[0]);
	//Pour une cellule au repos, on s'intéresse au nombre de cellules excitées dans le voisinage.
	int sum = 0;
	for(int i=0;i<neighborSize;i++){
		if(availableStates[2]->id == neighbors[i]->state.id) sum+=1;
	}
	//Toute cellule au repos ayant exactement 2 voisinges excitées devient excitée.
	if(c.State.getid()==availableStates[0]->id && sum==2)
		return new Cell(availableStates[2]);
}