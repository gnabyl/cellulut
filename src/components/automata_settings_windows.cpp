#include"automata_settings_windows.h"



NeighborsBrowseWindow::NeighborsBrowseWindow(){
    mainLayout = new QVBoxLayout(this);
    QDialog *neighborhoodSettings = new QDialog;
    neighborhoodSettings->setWindowTitle("Neighborhood settings");
    //Automata spinbox
    neighborhoodCbb = new QComboBox(this);
    neighborhoodLayout = new QFormLayout;
    neighborhoodLayout->addRow("Neighborhood", neighborhoodCbb);
    mainLayout->addLayout(neighborhoodLayout);
    QPushButton *Cancel = new QPushButton("Cancel", this);
    connect(Cancel, SIGNAL(clicked()), this, SLOT(quit()));
      }
