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

  public slots:
    void setNbRows(int nbRows);
    void setNbCols(int nbCols);
    void setCellSize(int size);
    void setAutomata(int index);
    void setNeighbor(NeighborhoodStrategy* neighbor);
    void setTransition(TransitionStrategy* transition);

    void changeCellState(int x, int y);
    void changeAnt(int x, int y);
    void setBufferSize(int size);
    void changeFrequency(int f);

    void btnPlayPauseClicked();
    void btnNextClicked();
    void btnResetClicked();
    void btnRandomClicked();
};

#endif // SIMULATOR_WIDGET_H
