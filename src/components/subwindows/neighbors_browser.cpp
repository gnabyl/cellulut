#include "neighbors_browser.h"

NeighborsBrowser::NeighborsBrowser(QWidget* parent) : QDialog(parent) {
    mainLayout = new QVBoxLayout(this);
    neighborhoodLayout = new QFormLayout(this);
    buttonsLayout = new QHBoxLayout(this);
    neighborhoodCbb = new QComboBox(this);

    neighborCreator = new NeighborCreator(this, 11, 11);

    btnConfirm = new QPushButton("Confirm", this);
    btnCreate = new QPushButton("Create", this);

    neighborhoodLayout->addRow("Neighborhood", neighborhoodCbb);

    connect(btnCreate, &QPushButton::clicked, this, &NeighborsBrowser::openNeighborCreator);
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

void NeighborsBrowser::openNeighborsBrowser(){
    std::pair<int, NeighborhoodStrategy**> loadedNeighborsInfos;
    try{
        loadedNeighborsInfos = DBManager::getDB().loadNeighborhoodFromDB();
        setNeighborhoods(loadedNeighborsInfos.first, loadedNeighborsInfos.second);
//        connect(neighborsBrowser, &NeighborsBrowser::neighborChanged, this, &ControlPanel::setNeighbor);
//        connect(neighborsBrowser, &NeighborsBrowser::neighborChanged, simulatorWidget, &SimulatorWidget::setNeighbor);
    }
    catch(DBException e){
        QMessageBox window;
        window.setText(QString::fromStdString(e.getInfo()));
        window.show();
    }

    this->exec();
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

void NeighborsBrowser::openNeighborCreator() {
    this->neighborCreator->exec();
}


// ================================== Creation ===================================
NeighborCreator::NeighborCreator(QWidget* parent, int width, int height) : QDialog(parent) {
    this->width = width;
    this->height = height;
    if (this->width % 2 == 0) {
        this->width ++;
    }
    if (this->height % 2 == 0) {
        this->height ++;
    }
    this->centerR = this->height / 2;
    this->centerC = this->width / 2;
    mainLayout = new QVBoxLayout(this);
    infoLayout = new QFormLayout(this);
    gridLayout = new QGridLayout(this);
    buttonsLayout = new QHBoxLayout(this);

    txtName = new QLineEdit();
    cellsCheckbox = new QCheckBox**[height];
    for (int r = 0; r < height; r ++) {
        cellsCheckbox[r] = new QCheckBox*[width];
        for (int c = 0; c < width; c ++) {
            if (r == centerR && c == centerC) {
                gridLayout->addWidget(new QLabel("|X|"), r, c);
            } else {
                cellsCheckbox[r][c] = new QCheckBox();
                gridLayout->addWidget(cellsCheckbox[r][c], r, c);
            }
        }
    }

    btnCreate = new QPushButton("Create");
    connect(btnCreate, &QPushButton::clicked, this, &NeighborCreator::createNeighbor);

    buttonsLayout->addWidget(btnCreate);

    infoLayout->addRow("Name", txtName);

    mainLayout->addLayout(infoLayout);
    mainLayout->addWidget(new QLabel("Choose neighbors"));
    mainLayout->addLayout(gridLayout);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);
}

void NeighborCreator::createNeighbor() {
    DBManager db = DBManager::getDB();
    int nbNeighbors = 0;
    int *dx, *dy;
    for (int r = 0; r < height; r ++) {
        for (int c = 0; c < width; c ++) {
            if (r != centerR || c != centerC) {
                if (cellsCheckbox[r][c]->isChecked())
                    nbNeighbors ++;
            }
        }
    }
    dx = new int[nbNeighbors];
    dy = new int[nbNeighbors];
    nbNeighbors = 0;
    for (int r = 0; r < height; r ++) {
        for (int c = 0; c < width; c ++) {
            if (r != centerR || c != centerC) {
                if (cellsCheckbox[r][c] && cellsCheckbox[r][c]->isChecked()) {
                    dx[nbNeighbors] = r - centerR;
                    dy[nbNeighbors] = c - centerC;
                    nbNeighbors ++;
                }
            }
        }
    }
    db.DBaddNeighborhood(txtName->text(), nbNeighbors, dx, dy);
    delete[] dx;
    delete[] dy;
}

NeighborCreator::~NeighborCreator() {

}
