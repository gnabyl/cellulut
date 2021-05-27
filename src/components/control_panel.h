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
#include <QSlider>
#include <QGroupBox>
#include <QLineEdit>
#include "simulator_widget.h"
#include "utils/automata_manager.h"
#include "automata_settings_windows.h"

class AutomataNameBox : public QLineEdit{
    Q_OBJECT

    using QLineEdit::QLineEdit; /*enables QLineEdit constructor to be used*/

signals:
    void automataChanged(int id);
public slots:
    void setAutomataName(int id);
};

class StateNameBox : public QLineEdit{
    Q_OBJECT

    using QLineEdit::QLineEdit;

//signals:
//    void stateChanged(int id);
//public slots:
//    void setStateName(int id);
};

class NeighborhoodNameBox : public QLineEdit{
    Q_OBJECT

    using QLineEdit::QLineEdit;

//signals:
//    void neighborhoodChanged(int id);
//public slots:
//    void setNeighborhoodName(int id);
};

class RuleNameBox : public QLineEdit{
    Q_OBJECT

    using QLineEdit::QLineEdit;

//signals:
//    void ruleChanged(int id);
//public slots:
//    void setRuleName(int id);
};

class FrequencyDisplayBox : public QLineEdit{
    Q_OBJECT

    using QLineEdit::QLineEdit;

public slots:
    void setFrequency(int);
};

class ControlPanel : public QWidget {
    Q_OBJECT

    QVBoxLayout* mainLayout;

    //Automata Spinbox
    QFormLayout* automatasLayout;
    QComboBox* automataCbb;

    //Grid settings box
    QGroupBox* gridSettingsBox;
    QVBoxLayout* gridSettingsLayout;
    QSpinBox* nbRowsSpb, *nbColsSpb, *cellSizeSpb;
    QFormLayout* nbRowsLayout;
    QFormLayout* nbColsLayout;
    QFormLayout* cellSizeLayout;

    //Automata settings box
    QGroupBox* automataSettingsBox;
    QVBoxLayout* automataSettingsLayout;
        //Choose automata
    QLabel* automataLabel;
    QPushButton* btnBrowseAutomatas;
    AutomataNameBox* textAutomataName;
    QHBoxLayout* automataFieldLayout;

        //Chose states
    QLabel** statesLabels;
    QPushButton** btnBrowseStates;
    StateNameBox** textStatesNames;
    QHBoxLayout** statesFieldLayout;

        //Chose neighborhood
    QLabel* neighborhoodLabel;
    NeighborhoodNameBox* textNeighborhoodName;
    QPushButton* btnBrowseNeighborhoods;
    QHBoxLayout* neighborhoodFieldLayout;

        //Chose transition rule
    QLabel* ruleLabel;
    RuleNameBox* textRuleName;
    QPushButton* btnBrowseRules;
    QHBoxLayout* ruleFieldLayout;

    //Run settings box
    QGroupBox* runSettingsBox;
    QVBoxLayout* runSettingsLayout;
    QSlider* sliderSpeed;
    QLabel* speedLabel;
    QSpinBox* bufferSizeSpb;
    FrequencyDisplayBox* textSpeed;
    QHBoxLayout* sliderSpeedLayout;
    QFormLayout* bufferSizeFieldLayout;

    SimulatorWidget* simulatorWidget;
    AutomataManager* automataManager;

  public:
    explicit ControlPanel(QWidget* parent, SimulatorWidget* simulatorWidget);
    ~ControlPanel();

    void initGridSettings();
    void initAutomataSettings();
    void initRunSettings();

    void setNbRows(int nbRows);
    void setNbCols(int nbCols);
    void setCellSize(int cellSize);

    void loadAutomatas();
    void initEventHandler();

public slots:
    void changeAutomataName(int id);


  signals:
    private slots:
    void stateSettings();
    void neighborhoodSetting();
    void transitionSetting();
    void automataChanged(int id){};

};

#endif // CONTROL_PANEL_H
