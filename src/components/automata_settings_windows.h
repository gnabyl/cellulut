#ifndef AUTOMATA_SETTINGS_WINDOWS_H
#define AUTOMATA_SETTINGS_WINDOWS_H

#include <QDialog>
#include <QPushButton>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QGroupBox>
#include "utils/neighborhood_strategy.h"
class StateBrowseWindow : public QDialog{
    Q_OBJECT

public:
    StateBrowseWindow(){
        QDialog *stateSettings = new QDialog;
        stateSettings->setWindowTitle("State settings");
        QPushButton *confirm = new QPushButton("Cancel", this);
        connect(confirm, SIGNAL(clicked()), stateSettings, SLOT(quit()));
    };
    ~StateBrowseWindow(){};
};

class NeighborsBrowseWindow : public QDialog{
    Q_OBJECT
    //neigborhood Spinbox
    QVBoxLayout* mainLayout;
    QFormLayout* neighborhoodLayout;
    QComboBox* neighborhoodCbb;
    QGroupBox* radiusSetting;
    QSpinBox* radius;

public:
    NeighborsBrowseWindow();
    ~NeighborsBrowseWindow(){};

};

class TransitionBrowseWindow : public QDialog {
    Q_OBJECT
    //transition Spinbox
    QVBoxLayout* mainLayout;
    QFormLayout* transitionLayout;
    QComboBox* transitionCbb;
    QFormLayout* directionLayout;
    QComboBox* directionCbb;

public:
    TransitionBrowseWindow();
    ~TransitionBrowseWindow(){};
};



#endif // AUTOMATA_SETTINGS_WINDOWS_H
