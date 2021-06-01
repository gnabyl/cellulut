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
#include <QGroupBox>
#include <QLineEdit>
#include "simulator_widget.h"
//#include "automata_settings_windows.h"
#include "bslider.h"
#include "utils/automata_manager.h"
#include "subwindows/automatas_browser.h"
#include "subwindows/neighbors_browser.h"
#include "subwindows/transitions_browser.h"

class FrequencyDisplayBox : public QLineEdit{
    Q_OBJECT

    using QLineEdit::QLineEdit;

public slots:
    void setFrequency(int);
};

class ControlPanel : public QWidget {
    Q_OBJECT

    QVBoxLayout* mainLayout;

    //Grid settings box
    QGroupBox* gridSettingsBox;
    QFormLayout* gridSettingsLayout;
    QSpinBox* nbRowsSpb, *nbColsSpb, *cellSizeSpb;

    //Automata settings box
    QGroupBox* automataSettingsBox;
    QVBoxLayout* automataSettingsLayout;

    //Choose automata
    QLabel* automataLabel;
    QPushButton* btnBrowseAutomatas;
    QLineEdit* textAutomataName;
    QHBoxLayout* automataFieldLayout;

    //Chose states
    QLabel** statesLabels;
    QPushButton** btnBrowseStates;
    QLineEdit** textStatesNames;
    QHBoxLayout** statesFieldLayout;

    //Chose neighborhood
    QLabel* neighborhoodLabel;
    QLineEdit* textNeighborhoodName;
    QPushButton* btnBrowseNeighborhoods;
    QHBoxLayout* neighborhoodFieldLayout;

    //Chose transition rule
    QLabel* ruleLabel;
    QLineEdit* textTransitionName;
    QPushButton* btnBrowseRules;
    QHBoxLayout* ruleFieldLayout;

    //Run settings box
    QGroupBox* runSettingsBox;
    BSlider* sliderSpeed;
    QLabel* speedLabel;
    QSpinBox* bufferSizeSpb;
    QFormLayout* runSettingsLayout;

    SimulatorWidget* simulatorWidget;
    AutomataManager* automataManager;

    // Popups
    AutomatasBrowser* automatasBrowser;
    NeighborsBrowser* neighborsBrowser;
    TransitionsBrowser* transitionsBrowser;

    void loadAutomatas();
    void loadNeighborhoods();
    void loadTransitions();

  public:
    explicit ControlPanel(QWidget* parent, SimulatorWidget* simulatorWidget);
    ~ControlPanel();

    void initGridSettings();
    void initAutomataSettings();
    void initRunSettings();

    void setNbRows(int nbRows);
    void setNbCols(int nbCols);
    void setCellSize(int cellSize);

    void initEventHandler();

  signals:
    void automataChanged(int id);
  private slots:
    void stateSettings();
    void openNeighborsBrowser();

    void setAutomata(int id);
    void setNeighbor(NeighborhoodStrategy* neighbor);
    void setTransition(TransitionStrategy* transition);

    void openTransitionsBrowser();

    void openAutomatasBrowser();
};

#endif // CONTROL_PANEL_H
