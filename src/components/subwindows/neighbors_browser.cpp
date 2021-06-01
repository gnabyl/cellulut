#include "neighbors_browser.h"

NeighborsBrowser::NeighborsBrowser(QWidget* parent) : QDialog(parent) {
    mainLayout = new QVBoxLayout(this);
    neighborhoodLayout = new QFormLayout(this);

    neighborhoodCbb = new QComboBox(this);

    neighborhoodLayout->addRow("Neighborhood", neighborhoodCbb);


    mainLayout->addLayout(neighborhoodLayout);
}

NeighborsBrowser::~NeighborsBrowser() {

}

void NeighborsBrowser::setNeighborhoods(int nbNeighbors, NeighborhoodStrategy **neighbors) {
    this->nbNeighbors = nbNeighbors;
    this->neighbors = neighbors;
    updateCombobox();
}

void NeighborsBrowser::updateCombobox() {
    neighborhoodCbb->clear();
    for (int i = 0; i < nbNeighbors; i ++) {
        neighborhoodCbb->addItem(neighbors[i]->getName().c_str());
    }
}
