//
// Created by Téva Ducoté on 23/04/2021.
//

#include "neighborhoodStrategy.h"
#include <cmath>

VonNeumannNeighborhood::VonNeumannNeighborhood(const int hauteur, const int largeur): neighborhood(new std::pair<int,int>[hauteur*largeur][nb_neighbors]) {
    neighborhood= new std::pair<int,int>* [hauteur*largeur];
    for (int i = 0; i <hauteur*largeur ; i++) {
        neighborhood[i]= new std::pair<int,int>[this->nb_neighbors];
    }
    int m=0; // numero de la cellule
    for(unsigned int i=0;i<hauteur;i++){
        for (unsigned j = 0; j <largeur ; j++) {
            int n=0; // indice voisin de la cellule
            for (int k = i-1; k <i+1 ; k++) {
                for (int l = j-1; l <j+1 ; l++) {
                    //coordonnée cellule voisine
                    int x=(k+hauteur)%hauteur;
                    int y =(l+largeur)%largeur;
                    if((fabs(x-1)+fabs(y-j))==1){
                       neighborhood[m]=Grid::getCell(x,y);
                        n++;
                    }
                }
            }
            m++;
        }
    }
}

VonNeumannNeighborhoodGeneralized::VonNeumannNeighborhoodGeneralized(const int hauteur,const int largeur, unsigned int radius):nb_neighbors(radius^2+(radius+1)^(2)-1 ){
    neighborhood= new std::pair<int,int>* [hauteur*largeur];
    for (int i = 0; i <hauteur*largeur ; i++) {
        neighborhood[i]= new std::pair<int,int>[this->nb_neighbors];
    }
    int m=0; // numero de la cellule
    for(unsigned int i=0;i<hauteur;i++){
        for (unsigned j = 0; j <largeur ; j++) {
            int n=0; // indice voisin de la cellule
            for (int k = i-radius; k <i+radius ; k++) {
                for (int l = j-radius; l <j+radius ; l++) {
                    //coordonnée cellule voisine
                    int x=(k+hauteur)%hauteur;
                    int y =(l+largeur)%largeur;
                    if((fabs(x-i)+ fabs(y-j))>0 && (fabs(x-i)+fabs(y-j))<=radius){
                        neighborhood[m]=Grid::getCell(x,y);
                        n++;
                    }
                }
            }
            m++;
        }
    }
}

MooreNeighborhood::MooreNeighborhood(const int hauteur, const int largeur){
    neighborhood= new std::pair<int,int>* [hauteur*largeur];
    for (int i = 0; i <hauteur*largeur ; i++) {
        neighborhood[i]= new std::pair<int,int>[this->nb_neighbors];
    }
    int m=0; // numero de la cellule
    for(unsigned int i=0;i<hauteur;i++){
        for (unsigned j = 0; j <largeur ; j++) {
            int n=0; // indice voisin de la cellule
            for (int k = i-1; k <i+1 ; k++) {
                for (int l = j-1; l <j+1 ; l++) {
                    //coordonnée cellule voisine
                    int x=(k+hauteur)%hauteur;
                    int y =(l+largeur)%largeur;
                    if(fabs(x-i)==1 && fabs(y-j)==1){
                        neighborhood[m][n]=Grid::getCell(x,y);
                        n++;
                    }
                }
            }
            m++;
        }
    }
}

MooreNeighborhoodGeneralized::MooreNeighborhoodGeneralized(const int hauteur,const int largeur, unsigned int radius):nb_neighbors((2*radius+1)^(2)-1){
    neighborhood= new std::pair<int,int>* [hauteur*largeur];
    for (int i = 0; i <hauteur*largeur ; i++) {
        neighborhood[i]= new std::pair<int,int>[this->nb_neighbors];
    }
    int m=0; // numero de la cellule
    for(unsigned int i=0;i<hauteur;i++){
        for (unsigned j = 0; j <largeur ; j++) {
            int n=0; // indice voisin de la cellule
            for (int k = i-radius; k <i+radius ; k++) {
                for (int l = j-radius; l <j+radius ; l++) {
                    //coordonnée cellule voisine
                    int x=(k+hauteur)%hauteur;
                    int y =(l+largeur)%largeur;
                    if(0<fabs(x-i) && 0<fabs(y-j) && fabs(x-i)<=radius && fabs(y-j)<=radius){
                        neighborhood[m][n]=Grid::getCell(x,y);
                        n++;
                    }
                }
            }
            m++;
        }
    }
}