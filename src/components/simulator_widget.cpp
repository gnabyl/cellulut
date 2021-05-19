#include "simulator_widget.h"
#include <iostream>
void SimulatorWidget::initLayout() {
    simulatorLayout = new QVBoxLayout(this);
    gridLayout = new QGridLayout(this);
    controllerLayout = new QHBoxLayout(this);
    configBtnLayout = new QHBoxLayout(this);
}

void SimulatorWidget::setButtonIcon(QPushButton* btn, const QString& path) {
    btn->setIcon(QIcon(path));
    btn->setIconSize(QSize(28, 28));
    btn->setFixedSize(30, 30);
}

void SimulatorWidget::btnNextClicked() {
    try {
        simulator->next();
        updateGridDisplay();
    }  catch (TransitionException e) {
        QMessageBox msgBox;
        msgBox.setText(QString(e.getInfo().c_str()));
        msgBox.exec();
    }
}

void SimulatorWidget::initButtons() {
    btnPlay = new QPushButton(this);
    btnPrev = new QPushButton(this);
    btnNext = new QPushButton(this);
    btnReset = new QPushButton(this);

    setButtonIcon(btnPrev, ":assets/previous-button.png");
    setButtonIcon(btnPlay, ":assets/play-button.png");
    setButtonIcon(btnReset, ":assets/reset-button.png");
    setButtonIcon(btnNext, ":assets/next-button.png");

    controllerLayout->setSizeConstraint(QLayout::SetMinimumSize);

    controllerLayout->addWidget(btnPrev);
    controllerLayout->addWidget(btnPlay);
    controllerLayout->addWidget(btnReset);
    controllerLayout->addWidget(btnNext);

    connect(btnNext, &QPushButton::clicked, this, &SimulatorWidget::btnNextClicked);
}

void SimulatorWidget::regenerateRandomGrid() {
    if (this->simulator->getAutomata() == nullptr) {
        return;
    }
    this->simulator->setStartGrid(new Grid(simulator->getAutomata()->getNbStates(),
                                           simulator->getAutomata()->getAvailableStates(),
                                           this->nbCols, this->nbRows));
}

void SimulatorWidget::updateGridDisplay() {
    Grid* currentGrid = simulator->getIterator().current();
    if (currentGrid == nullptr) {
        return;
    }
    for (int r = 0; r < nbRows; r ++) {
        for (int c = 0; c < nbCols; c ++) {
            cellWidgets[r * nbCols + c]->setColor(currentGrid->getCell(r, c)->getState()->getColor());
            cellWidgets[r * nbCols + c]->setSize(cellSize);
        }
    }
}

void SimulatorWidget::resetGridDisplay() {
    Grid* currentGrid = simulator->getIterator().current();
    if (currentGrid == nullptr) {
        return;
    }
    gridLayout->setAlignment(Qt::AlignCenter);
    gridLayout->setSpacing(2);
    cellWidgets = new CellWidget*[nbRows * nbCols];
    for (int r = 0; r < nbRows; r ++) {
        for (int c = 0; c < nbCols; c ++) {
            cellWidgets[r * nbCols + c] = new CellWidget(this, cellSize, r, c, QString(currentGrid->getCell(r, c)->getState()->getLabel().c_str()));
            cellWidgets[r * nbCols + c]->setColor(currentGrid->getCell(r, c)->getState()->getColor());
            gridLayout->addWidget(cellWidgets[r * nbCols + c], r, c);
        }
    }
    adjustSize();
}

int SimulatorWidget::getNbRows() const {
    return this->nbRows;
}
void SimulatorWidget::setNbRows(int nbRows) {
    cleanGrid();
    this->nbRows = nbRows;
    regenerateRandomGrid();
    resetGridDisplay();
}
int SimulatorWidget::getNbCols() const {
    return this->nbCols;
}
void SimulatorWidget::setNbCols(int nbCols) {
    cleanGrid();
    this->nbCols = nbCols;
    regenerateRandomGrid();
    resetGridDisplay();
}
void SimulatorWidget::setCellSize(int size) {
    this->cellSize = size;
    updateGridDisplay();
}

void SimulatorWidget::setAutomata(int index) {
    this->simulator->setAutomata(AutomataManager::getAutomataManager()->getAutomata(index));
    cleanGrid();
    regenerateRandomGrid();
    resetGridDisplay();
}

SimulatorWidget::SimulatorWidget(QWidget* parent, int nbRows, int nbCols, int cellSize) : QWidget(parent) {
    simulator = new Simulator(nullptr, 100);

    this->nbCols = nbCols;
    this->nbRows = nbRows;
    this->cellSize = cellSize;

    initLayout();
    initButtons();
    resetGridDisplay();

    simulatorLayout->addLayout(gridLayout);
    simulatorLayout->addLayout(controllerLayout);

    setLayout(simulatorLayout);

    adjustSize();
}

void SimulatorWidget::cleanGrid() {
    if (cellWidgets == nullptr) {
        return;
    }
    for (int r = 0; r < nbRows; r ++) {
        for (int c = 0; c < nbCols; c ++) {
            gridLayout->removeWidget(cellWidgets[r * nbCols + c]);
            delete cellWidgets[r * nbCols + c];
        }
    }
    delete [] cellWidgets;
    cellWidgets = nullptr;
}

SimulatorWidget::~SimulatorWidget() {
    cleanGrid();
}
