#include "neighbors_browser.h"

NeighborsBrowser::NeighborsBrowser(QWidget* parent) : QDialog(parent) {
    mainLayout = new QVBoxLayout(this);
    neighborhoodLayout = new QFormLayout(this);
    buttonsLayout = new QHBoxLayout(this);
    neighborhoodCbb = new QComboBox(this);

    btnConfirm = new QPushButton("Confirm", this);
    btnCreate = new QPushButton("Create", this);

    neighborhoodLayout->addRow("Neighborhood", neighborhoodCbb);

    connect(btnConfirm, &QPushButton::clicked, this, &NeighborsBrowser::chooseNeighbor);
    connect(neighborhoodCbb, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &NeighborsBrowser::neighborCbbChanged);

    mainLayout->addLayout(neighborhoodLayout);

    buttonsLayout->addWidget(btnConfirm);
    buttonsLayout->addWidget(btnCreate);

    mainLayout->addLayout(buttonsLayout);

    adjustSize();
}

NeighborsBrowser::~NeighborsBrowser() {
    delete spbRadius;
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
    if (instanceof<VonNeumannNeighborhoodGeneralized>(selectedNeighbor) || instanceof<MooreNeighborhoodGeneralized>(selectedNeighbor)) {
        spbRadius = new QSpinBox();
        if (instanceof<VonNeumannNeighborhoodGeneralized>(selectedNeighbor)) {
            spbRadius->setValue(static_cast<const VonNeumannNeighborhoodGeneralized*>(selectedNeighbor)->getRadius());
        } else if (instanceof<MooreNeighborhoodGeneralized>(selectedNeighbor)) {
            spbRadius->setValue(static_cast<const MooreNeighborhoodGeneralized*>(selectedNeighbor)->getRadius());
        }
        if (neighborhoodLayout->rowCount() < 2) {
            neighborhoodLayout->addRow("Radius", spbRadius);
        }
    } else if (neighborhoodLayout->rowCount() >= 2) {
        neighborhoodLayout->removeRow(1);
    }
}

void NeighborsBrowser::chooseNeighbor() {
    emit neighborChanged(selectedNeighbor);
    close();
}
