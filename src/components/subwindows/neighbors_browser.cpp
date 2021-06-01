#include "neighbors_browser.h"

NeighborsBrowser::NeighborsBrowser(QWidget* parent) : QDialog(parent) {
    mainLayout = new QVBoxLayout(this);
    neighborhoodLayout = new QFormLayout(this);
    neighborhoodCbb = new QComboBox(this);

    btnConfirm = new QPushButton("Confirm", this);

    neighborhoodLayout->addRow("Neighborhood", neighborhoodCbb);

    connect(btnConfirm, &QPushButton::clicked, this, &NeighborsBrowser::chooseNeighbor);
    connect(neighborhoodCbb, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &NeighborsBrowser::neighborCbbChanged);

    mainLayout->addLayout(neighborhoodLayout);
    mainLayout->addWidget(btnConfirm);

    adjustSize();
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

void NeighborsBrowser::neighborCbbChanged(int id) {
    selectedNeighbor = neighbors[id];
}

void NeighborsBrowser::chooseNeighbor() {
    emit neighborChanged(selectedNeighbor);
    close();
}
