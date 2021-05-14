#ifndef CONTROL_PANEL_H
#define CONTROL_PANEL_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QString>
#include "simulator_widget.h"

class ControlPanel : public QWidget
{
    Q_OBJECT
    QFormLayout *gridConfigLayout;
    QSpinBox *nbRowsSpb, *nbColsSpb, *cellSizeSpb;


    QFormLayout *automatasLayout;
    QComboBox *automataCbb;

    QHBoxLayout *automataBtnLayout;
    QPushButton *automataCreateBtn, *automataSaveBtn, *automataDeleteBtn, *automataLoadBtn;

    QVBoxLayout *mainLayout;

    SimulatorWidget *simulatorWidget;
public:
    explicit ControlPanel(QWidget *parent, SimulatorWidget *simulatorWidget);
    ~ControlPanel();

    void setNbRows(int nbRows);
    void setNbCols(int nbCols);
    void setCellSize(int cellSize);

    void setAutomatas();
    void initEventHandler();


signals:

};

#endif // CONTROL_PANEL_H
