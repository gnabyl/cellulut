#ifndef AUTOMATA_SETTINGS_WINDOWS_H
#define AUTOMATA_SETTINGS_WINDOWS_H

#include <QDialog>
#include <QPushButton>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QVariant>
#include "utils/neighborhood_strategy.h"
class StateBrowseWindow : public QDialog{
    Q_OBJECT
    QVBoxLayout* mainLayout;
    QFormLayout* stateLayout;
    QComboBox* stateCbb;
    QLabel* nameStateLabel;
public:
    StateBrowseWindow();
    ~StateBrowseWindow(){};

};


class NeighborsBrowseWindow : public QDialog{
    Q_OBJECT
    QVBoxLayout* mainLayout;
    QFormLayout* neighborhoodLayout;
    QComboBox* neighborhoodCbb;
    QGroupBox* radiusSetting;
    QSpinBox* radius;


public:
    NeighborsBrowseWindow();
    ~NeighborsBrowseWindow(){};
private slots:
    void clickedactions(int indexItem);

};

class TransitionBrowseWindow : public QDialog {
    Q_OBJECT
    //transition Spinbox
    QVBoxLayout* mainLayout;
    QFormLayout* transitionLayout;
    QComboBox* transitionCbb;
    QFormLayout* directionLayout;
    QComboBox* directionCbb;
    QPushButton *Confirm;


public:
    TransitionBrowseWindow();
    ~TransitionBrowseWindow(){};
private slots:
    void clickedaction(int indexItem);

};



#endif // AUTOMATA_SETTINGS_WINDOWS_H
