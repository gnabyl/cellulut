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
    /**
     * @brief cellSize taille de chacune des cellules
     */
    int cellSize;
    /**
     * @brief nbCols nombre de colonnes
     */
    int nbCols;
    /**
     * @brief nbRows nombre de lignes
     */
    int nbRows;
    /**
     * @brief simulatorLayout layout vertical de type box qui regroupera les layout grid et controller
     */
    QVBoxLayout* simulatorLayout;
    /**
     * @brief gridLayout layout qui contiendra la grille avec les cellules
     */
    QGridLayout* gridLayout;
    /**
     * @brief controllerLayout layout qui contiendra les boutons pour lancer, mettre sur pause, passer à la génération suivante, précédente
     */
    QHBoxLayout* controllerLayout;
    /**
     * @brief configBtnLayout layout qui contiendra le bouton de la configuration
     */
    QHBoxLayout* configBtnLayout;

    /**
     * @brief cellWidgets tableau de cellwidget qui permetttra de pouvoir changer les caractéristiques de chaque cellule
     */
    CellWidget** cellWidgets = nullptr;

    /**
     * @brief lblCurrentGeneration information sur le numéro de la génération actuelle
     */
    QLabel* lblCurrentGeneration;
    /**
     * @brief btnPlay, tnPrev, btnNext, btnReset, btnRandom
     */
    QPushButton* btnPlay, *btnPrev, *btnNext, *btnReset, *btnRandom;
    /**
     * @brief timer permettra d'augemnter la fréquence des générations
     */
    QTimer* timer;
    int frequency;

    Simulator* simulator;
    /**
     * @brief playing pour vérifier si on a mis la génération sur pause ou pas
     */
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
    void stateHasChanged();

  public slots:
    void setNbRows(int nbRows);
    void setNbCols(int nbCols);
    void setCellSize(int size);
    void setAutomata(int index);
    void setNeighbor(NeighborhoodStrategy* neighbor);
    void setTransition(TransitionStrategy* transition);
    void setState(int nb, CellState* c);
    void setConfig(Grid* config);

    void changeCellState(int x, int y);
    void changeAnt(int x, int y);
    void setBufferSize(int size);
    void changeFrequency(int f);

    void btnPlayPauseClicked();
    void btnNextClicked();
    void btnResetClicked();
    void btnRandomClicked();
    void btnPrevClicked();
};

#endif // SIMULATOR_WIDGET_H
