#include"automata_settings_windows.h"

NeighborsBrowseWindow::NeighborsBrowseWindow(){

    mainLayout = new QVBoxLayout(this);
    neighborhoodLayout = new QFormLayout(this);
    radiusSetting = new QGroupBox(tr("Radius Setting"));
    QDialog *neighborhoodSettings = new QDialog;
    neighborhoodSettings->setWindowTitle("Neighborhood settings");

    neighborhoodCbb = new QComboBox(this);
    neighborhoodCbb->addItem("Von Neumann Neighborhood");
    neighborhoodCbb->addItem("Von Neumann Neighborhood Generalized");
    neighborhoodCbb->addItem("Moore Neighborhood");
    neighborhoodCbb->addItem("Moore Neighborhood Generalized");
    neighborhoodCbb->addItem("Arbitrary Neighborhood");

    neighborhoodLayout->addRow("Neighborhood", neighborhoodCbb);

    if (neighborhoodCbb->currentText()=="Von Neumann Neighborhood") {

    }
    if(neighborhoodCbb->currentText()=="Von Neumann Neighborhood Generalized"){
        radius = new QSpinBox(radiusSetting);
        radius->setKeyboardTracking(false);
        radius->setValue(1);
        radius->setMinimum(1);
        radius->setMaximum(5);
        neighborhoodLayout->addRow("Radius :",radius);
        mainLayout->addLayout(neighborhoodLayout);


    }
    if (neighborhoodCbb->currentText()=="Moore Neighborhood") {

    }
    if(neighborhoodCbb->currentText()=="Moore Neighborhood Generalized"){
        radius = new QSpinBox(radiusSetting);
        radius->setKeyboardTracking(false);
        radius->setValue(1);
        radius->setMinimum(1);
        radius->setMaximum(5);
        neighborhoodLayout->addRow("Radius :",radius);
        mainLayout->addLayout(neighborhoodLayout);
    }
    else{
        radius = new QSpinBox(radiusSetting);
        radius->setKeyboardTracking(false);
        radius->setValue(1);
        radius->setMinimum(1);
        radius->setMaximum(5);
        neighborhoodLayout->addRow("Radius :",radius);
        mainLayout->addLayout(neighborhoodLayout);
    }




    QPushButton *Confirm = new QPushButton("Confirm", this);
    connect(Confirm, SIGNAL(clicked()), this, SLOT(quit()));
      }


TransitionBrowseWindow::TransitionBrowseWindow(){

    mainLayout = new QVBoxLayout(this);
    transitionLayout = new QFormLayout(this);
    QDialog *transitionSettings = new QDialog;
    transitionSettings->setWindowTitle("Transition settings");


    transitionCbb = new QComboBox(this);
    transitionCbb->addItem("Game Of Life Transition");
    transitionCbb->addItem("Brian's Brain Transition");
    transitionCbb->addItem("David Grieffath Transition");
    transitionCbb->addItem("Langton Loop Transition");
    transitionCbb->addItem("Langton Ant Transition");

    transitionLayout->addRow("Transition", transitionCbb);

    if (transitionCbb->currentText()=="Langton Ant Transition") {

        directionCbb = new QComboBox(this);
        directionCbb->addItem("Up");
        directionCbb->addItem("Down");
        directionCbb->addItem("Left");
        directionCbb->addItem("Right");

        transitionLayout->addRow("Direction", directionCbb);

    }
    /*
    if (neighborhoodCbb->currentText()=="Moore Neighborhood") {

    }
    if(neighborhoodCbb->currentText()=="Moore Neighborhood Generalized"){
        radius = new QSpinBox(radiusSetting);
        radius->setKeyboardTracking(false);
        radius->setValue(1);
        radius->setMinimum(1);
        radius->setMaximum(5);
        neighborhoodLayout->addRow("Radius :",radius);
        mainLayout->addLayout(neighborhoodLayout);
    }
    else{
        radius = new QSpinBox(radiusSetting);
        radius->setKeyboardTracking(false);
        radius->setValue(1);
        radius->setMinimum(1);
        radius->setMaximum(5);
        neighborhoodLayout->addRow("Radius :",radius);
        mainLayout->addLayout(neighborhoodLayout);
    }

*/


    QPushButton *Confirm = new QPushButton("Confirm", this);
    transitionLayout->addRow("", Confirm);
    mainLayout->addLayout(transitionLayout);

    connect(Confirm, SIGNAL(clicked()), this, SLOT(quit()));
}
