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
