#ifndef SIMULATOR_WIDGET_H
#define SIMULATOR_WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include <QMessageBox>
#include <QTimer>
#include "../constants.h"
#include "cell_widget.h"
#include "utils/simulator.h"
#include "utils/automata_manager.h"

class SimulatorWidget : public QWidget {
    Q_OBJECT
    int cellSize;
    int nbCols;
    int nbRows;

    QVBoxLayout* simulatorLayout;
    QGridLayout* gridLayout;
    QHBoxLayout* controllerLayout;
    QHBoxLayout* configBtnLayout;

    CellWidget** cellWidgets = nullptr;

    QLabel* lblCurrentGeneration;

    QPushButton* btnPlay, *btnPrev, *btnNext, *btnReset, *btnRandom;

    QTimer* timer;
    int frequency;

    Simulator* simulator;

    bool playing = false;


  public:
    SimulatorWidget(QWidget* parent, int width, int height, int cellSize);
    ~SimulatorWidget();
    void initLayout();
    void cleanGrid();
    void resetGridDisplay();
    void updateGridDisplay();
    void regenerateRandomGrid();
    void regenerateEmptyGrid();
    void initButtons();
    void setButtonIcon(QPushButton* btn, const QString& path);
    int getNbCols() const;
    int getNbRows() const;
    int getCellSize() const;
    int getFrequency() const;
    Simulator* getSimulator() const;
    void setFrequency(int f);

  signals:
    /**
     * @brief stateHasChanged signal appelé dans la méthode setState
     */
    void stateHasChanged();

  public slots:
    /**
     * @brief setNbRows change le nombre de lignes
     * @param nbRows nouveau nombre de lignes
     */
    void setNbRows(int nbRows);
    /**
     * @brief setNbCols change le nombre de colonnes
     * @param nbCols nouveau nombre de colonnes
     */
    void setNbCols(int nbCols);
    /**
     * @brief setCellSize change la taille des cellule
     * @param size nouvelle taille des cellules
     */
    void setCellSize(int size);
    /**
     * @brief setAutomata fait apparaître l'automate dans la grille
     * @param index numéro de l'automate
     */
    void setAutomata(int index);
    /**
     * @brief setNeighbor change le voisinage
     * @param neighbor nouveau type de voisinage
     */
    void setNeighbor(NeighborhoodStrategy* neighbor);
    /**
     * @brief setTransition change la transition
     * @param transition nouveau type de transition
     */
    void setTransition(TransitionStrategy* transition);
    /**
     * @brief setState change l'état d'une cellule
     * @param nb nombre d'état de l'automate
     * @param c nouvelle état de la cellule
     */
    void setState(int nb, CellState* c);
    /**
     * @brief setConfig change la configuration de la grille
     * @param config grille à rentrer dans l'automate
     */
    void setConfig(Grid* config);
    /**
     * @brief changeCellState change l'état d'une cellule
     * @param x position x de la cellule
     * @param y position y de la cellule
     */
    void changeCellState(int x, int y);
    /**
     * @brief changeAnt change la position de la fourmi
     * @param x position x de la fourmi
     * @param y position y de la fourmi
     */
    void changeAnt(int x, int y);
    /**
     * @brief setBufferSize change la taille du buffer
     * @param size nouvelle taille du buffer
     */
    void setBufferSize(int size);
    /**
     * @brief changeFrequency change la vitesse du simulateur
     * @param f nouvelle fréquence
     */
    void changeFrequency(int f);
    /**
     * @brief btnPlayPauseClicked fonction qui met en pause ou lance le simulateur
     */
    void btnPlayPauseClicked();
    /**
     * @brief btnNextClicked fonction qui affiche la grille suivante
     */
    void btnNextClicked();
    /**
     * @brief btnResetClicked fonction qui permet de revenir à la grille de départ
     */
    void btnResetClicked();
    /**
     * @brief btnRandomClicked fonction qui génère une grille aléatoire
     */
    void btnRandomClicked();
    /**
     * @brief btnPrevClicked fonction qui affiche la grille précédente
     */
    void btnPrevClicked();
};

#endif // SIMULATOR_WIDGET_H
