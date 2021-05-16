#ifndef SIMULATOR_WIDGET_H
#define SIMULATOR_WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QIcon>
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

    CellWidget** cellWidgets;

    QPushButton* btnPlay, *btnPrev, *btnNext, *btnReset;

    Simulator* simulator;


  public:
    SimulatorWidget(QWidget* parent, int width, int height, int cellSize);
    ~SimulatorWidget();
    void initLayout();
    void cleanGrid();
    void updateGrid();
    void initButtons();
    void setButtonIcon(QPushButton* btn, const QString& path);

  signals:

  private slots:
    void setNbRows(int nbRows);
    void setNbCols(int nbCols);
    void setCellSize(int size);
    void setAutomata(int index);
};

#endif // SIMULATOR_WIDGET_H
