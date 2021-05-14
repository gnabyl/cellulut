//
// Created by Téva Ducoté on 23/04/2021.
//

#include "neighborhood_strategy.h"
#include <cmath>

VonNeumannNeighborhood::VonNeumannNeighborhood(const Grid g):nb_cells(g.getHeight()*g.getWidth()){
    neighborhood= new Cell**[g.getHeight()*g.getWidth()];
    for (int i = 0; i <g.getHeight()*g.getWidth() ; i++) {
        neighborhood[i]= new Cell*[this->nb_neighbors];
    }
    int m=0; // numero de la cellule
    for(unsigned int i=0;i<g.getHeight();i++){
        for (unsigned j = 0; j <g.getWidth() ; j++) {
            int n=0; // indice voisin de la cellule
            for (int k = i-1; k <i+1 ; k++) {
                for (int l = j-1; l <j+1 ; l++) {
                    //coordonnée cellule voisine
                    int x=(k+g.getHeight())%g.getHeight();
                    int y =(l+g.getWidth())%g.getWidth();
                    if((fabs(x-1)+fabs(y-j))==1){
                       neighborhood[m][n]=g.getCell(x,y);
                        n++;
                    }
                }
            }
            m++;
        }
    }
}

VonNeumannNeighborhoodGeneralized::VonNeumannNeighborhoodGeneralized(const Grid g, unsigned int radius):nb_neighbors(radius^2+(radius+1)^(2)-1 ),nb_cells(g.getHeight()*g.getWidth()){
    neighborhood= new Cell**[g.getHeight()*g.getWidth()];
    for (int i = 0; i <g.getHeight()*g.getWidth() ; i++) {
        neighborhood[i]= new Cell*[this->nb_neighbors];
    }
    int m=0; // numero de la cellule
    for(unsigned int i=0;i<g.getHeight();i++){
        for (unsigned j = 0; j <g.getWidth() ; j++) {
            int n=0; // indice voisin de la cellule
            for (int k = i-radius; k <i+radius ; k++) {
                for (int l = j-radius; l <j+radius ; l++) {
                    //coordonnée cellule voisine
                    int x=(k+g.getHeight())%g.getHeight();
                    int y =(l+g.getWidth())%g.getWidth();
                    if((fabs(x-i)+ fabs(y-j))>0 && (fabs(x-i)+fabs(y-j))<=radius){
                        neighborhood[m][n]=g.getCell(x,y);
                        n++;
                    }
                }
            }
            m++;
        }
    }
}

MooreNeighborhood::MooreNeighborhood(const Grid g):nb_cells(g.getHeight()*g.getWidth()){
    neighborhood= new Cell**[g.getHeight()*g.getWidth()];
    for (int i = 0; i <g.getHeight()*g.getWidth() ; i++) {
        neighborhood[i]= new Cell*[this->nb_neighbors];
    }
    int m=0; // numero de la cellule
    for(unsigned int i=0;i<g.getHeight();i++){
        for (unsigned j = 0; j <g.getWidth() ; j++) {
            int n=0; // indice voisin de la cellule
            for (int k = i-1; k <i+1 ; k++) {
                for (int l = j-1; l <j+1 ; l++) {
                    //coordonnée cellule voisine
                    int x=(k+g.getHeight())%g.getHeight();
                    int y =(l+g.getWidth())%g.getWidth();
                    if(fabs(x-i)==1 && fabs(y-j)==1){
                        neighborhood[m][n]=g.getCell(x,y);
                        n++;
                    }
                }
            }
            m++;
        }
    }
}

MooreNeighborhoodGeneralized::MooreNeighborhoodGeneralized(const Grid g, unsigned int radius):nb_neighbors((2*radius+1)^(2)-1),nb_cells(g.getHeight()*g.getWidth()){
    neighborhood= new Cell**[g.getHeight()*g.getWidth()];
    for (int i = 0; i <g.getHeight()*g.getWidth() ; i++) {
        neighborhood[i]= new Cell*[this->nb_neighbors];
    }
    int m=0; // numero de la cellule
    for(unsigned int i=0;i<g.getHeight();i++){
        for (unsigned j = 0; j <g.getWidth() ; j++) {
            int n=0; // indice voisin de la cellule
            for (int k = i-radius; k <i+radius ; k++) {
                for (int l = j-radius; l <j+radius ; l++) {
                    //coordonnée cellule voisine
                    int x=(k+g.getHeight())%g.getHeight();
                    int y =(l+g.getWidth())%g.getWidth();
                    if(0<fabs(x-i) && 0<fabs(y-j) && fabs(x-i)<=radius && fabs(y-j)<=radius){
                        neighborhood[m][n]=g.getCell(x,y);
                        n++;
                    }
                }
            }
            m++;
        }
    }
}
