//
// Created by Téva Ducoté on 23/04/2021.
//

#include "neighborhood_strategy.h"
#include <cmath>

VonNeumannNeighborhood::VonNeumannNeighborhood(const Grid g): nb_cells(g.getHeight() * g.getWidth()) {
    neighborhood = new Cell** [g.getHeight()*g.getWidth()];
    for (int i = 0; i < g.getHeight()*g.getWidth() ; i++) {
        neighborhood[i] = new Cell*[this->nb_neighbors];
    }
    int m = 0; // numero de la cellule
    for(int i = 0; i < g.getHeight(); i++) {
        for (int j = 0; j < g.getWidth() ; j++) {
            int n = 0; // indice voisin de la cellule
            for (int k = i - 1; k < i + 1 ; k++) {
                for (int l = j - 1; l < j + 1 ; l++) {
                    //coordonnée cellule voisine
                    int x = (k + g.getHeight()) % g.getHeight();
                    int y = (l + g.getWidth()) % g.getWidth();
                    if((abs(x - 1) + abs(y - j)) == 1) {
                        neighborhood[m][n] = g.getCell(x, y);
                        n++;
                    }
                }
            }
            m++;
        }
    }
}

VonNeumannNeighborhoodGeneralized::VonNeumannNeighborhoodGeneralized(const Grid g, int radius): nb_neighbors(radius * radius + (radius + 1) * ((radius + 1)) - 1 ), nb_cells(g.getHeight() * g.getWidth()) {
    neighborhood = new Cell** [g.getHeight()*g.getWidth()];
    for (int i = 0; i < g.getHeight()*g.getWidth() ; i++) {
        neighborhood[i] = new Cell*[this->nb_neighbors];
    }
    int m = 0; // numero de la cellule
    for(int i = 0; i < g.getHeight(); i++) {
        for (int j = 0; j < g.getWidth() ; j++) {
            int n = 0; // indice voisin de la cellule
            for (int k = i - radius; k < i + radius ; k++) {
                for (int l = j - radius; l < j + radius ; l++) {
                    //coordonnée cellule voisine
                    int x = (k + g.getHeight()) % g.getHeight();
                    int y = (l + g.getWidth()) % g.getWidth();
                    if((abs(x - i) + abs(y - j)) > 0 && (abs(x - i) + abs(y - j)) <= radius) {
                        neighborhood[m][n] = g.getCell(x, y);
                        n++;
                    }
                }
            }
            m++;
        }
    }
}

MooreNeighborhood::MooreNeighborhood(const Grid g): nb_cells(g.getHeight() * g.getWidth()) {
    neighborhood = new Cell** [g.getHeight()*g.getWidth()];
    for (int i = 0; i < g.getHeight()*g.getWidth() ; i++) {
        neighborhood[i] = new Cell*[this->nb_neighbors];
    }
    int m = 0; // numero de la cellule
    for(int i = 0; i < g.getHeight(); i++) {
        for (int j = 0; j < g.getWidth() ; j++) {
            int n = 0; // indice voisin de la cellule
            for (int k = i - 1; k < i + 1 ; k++) {
                for (int l = j - 1; l < j + 1 ; l++) {
                    //coordonnée cellule voisine
                    int x = (k + g.getHeight()) % g.getHeight();
                    int y = (l + g.getWidth()) % g.getWidth();
                    if(abs(x - i) == 1 && abs(y - j) == 1) {
                        neighborhood[m][n] = g.getCell(x, y);
                        n++;
                    }
                }
            }
            m++;
        }
    }
}

MooreNeighborhoodGeneralized::MooreNeighborhoodGeneralized(const Grid g, int radius): nb_neighbors((2 * radius + 1) * (2 * radius + 1) - 1), nb_cells(g.getHeight() * g.getWidth()) {
    neighborhood = new Cell** [g.getHeight()*g.getWidth()];
    for (int i = 0; i < g.getHeight()*g.getWidth() ; i++) {
        neighborhood[i] = new Cell*[this->nb_neighbors];
    }
    int m = 0; // numero de la cellule
    for(int i = 0; i < g.getHeight(); i++) {
        for (int j = 0; j < g.getWidth() ; j++) {
            int n = 0; // indice voisin de la cellule
            for (int k = i - radius; k < i + radius ; k++) {
                for (int l = j - radius; l < j + radius ; l++) {
                    //coordonnée cellule voisine
                    int x = (k + g.getHeight()) % g.getHeight();
                    int y = (l + g.getWidth()) % g.getWidth();
                    if(0 < abs(x - i) && 0 < abs(y - j) && abs(x - i) <= radius && abs(y - j) <= radius) {
                        neighborhood[m][n] = g.getCell(x, y);
                        n++;
                    }
                }
            }
            m++;
        }
    }
}
