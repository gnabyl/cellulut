#include "simulator_widget.h"
#include <iostream>
void SimulatorWidget::initLayout() {
    simulatorLayout = new QVBoxLayout(this);
    gridLayout = new QGridLayout(this);
    controllerLayout = new QHBoxLayout(this);
    configBtnLayout = new QHBoxLayout(this);

    gridLayout->setAlignment(Qt::AlignCenter);
    gridLayout->setSpacing(2);
}

void SimulatorWidget::setButtonIcon(QPushButton* btn, const QString& path) {
    btn->setIcon(QIcon(path));
    btn->setIconSize(QSize(48, 48));
    btn->setFixedSize(48, 48);
    btn->setStyleSheet("border-radius : 50;");
}

void SimulatorWidget::btnPlayPauseClicked() {
    if (!playing) {
        playing = true;
        timer->start(1000);
        setButtonIcon(btnPlay, PAUSE_BTN_ICON_PATH);
    } else {
        playing = false;
        timer->stop();
        setButtonIcon(btnPlay, PLAY_BTN_ICON_PATH);
    }
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

void SimulatorWidget::btnResetClicked() {
    try {
        simulator->reset();
        updateGridDisplay();
    }  catch (TransitionException e) {
        QMessageBox msgBox;
        msgBox.setText(QString(e.getInfo().c_str()));
        msgBox.exec();
    }
}

void SimulatorWidget::btnRandomClicked(){
    if(playing){
        playing = false;
        timer->stop();
        setButtonIcon(btnPlay, PLAY_BTN_ICON_PATH);
    }
    regenerateRandomGrid();
    updateGridDisplay();
}


void SimulatorWidget::initButtons() {
    btnPlay = new QPushButton(this);
    btnPrev = new QPushButton(this);
    btnNext = new QPushButton(this);
    btnReset = new QPushButton(this);
    btnRandom = new QPushButton(this);

    setButtonIcon(btnPrev, PREV_BTN_ICON_PATH);
    setButtonIcon(btnPlay, PLAY_BTN_ICON_PATH);
    setButtonIcon(btnReset, RESET_BTN_ICON_PATH);
    setButtonIcon(btnNext, NEXT_BTN_ICON_PATH);
    setButtonIcon(btnRandom, RANDOM_BTN_ICON_PATH);

    controllerLayout->setSizeConstraint(QLayout::SetMinimumSize);

    controllerLayout->addWidget(btnPrev);
    controllerLayout->addWidget(btnPlay);
    controllerLayout->addWidget(btnReset);
    controllerLayout->addWidget(btnRandom);
    controllerLayout->addWidget(btnNext);

    connect(btnPlay, &QPushButton::clicked, this, &SimulatorWidget::btnPlayPauseClicked);
    connect(btnNext, &QPushButton::clicked, this, &SimulatorWidget::btnNextClicked);
    connect(btnReset, &QPushButton::clicked, this, &SimulatorWidget::btnResetClicked);
    connect(btnRandom, &QPushButton::clicked, this, &SimulatorWidget::btnRandomClicked);
}

void SimulatorWidget::regenerateRandomGrid() {
    if (this->simulator->getAutomata() == nullptr) {
        return;
    }
    this->simulator->setStartGrid(new Grid(simulator->getAutomata()->getNbStates(),
                                           simulator->getAutomata()->getAvailableStates(),
                                           this->nbCols, this->nbRows));
}

void SimulatorWidget::regenerateEmptyGrid() {
    if (this->simulator->getAutomata() == nullptr) {
        return;
    }
    this->simulator->setStartGrid(new Grid(simulator->getAutomata()->getAvailableStates()[0],
                                           this->nbCols, this->nbRows));
}

void SimulatorWidget::updateGridDisplay() {
    Grid* currentGrid = simulator->getIterator().current();
    if (currentGrid == nullptr) {
        return;
    }
    lblCurrentGeneration->setText(tr("Generation #").append(QString::number(simulator->getCurrentGridID())));
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
    cellWidgets = new CellWidget*[nbRows * nbCols];
    for (int r = 0; r < nbRows; r ++) {
        for (int c = 0; c < nbCols; c ++) {
            cellWidgets[r * nbCols + c] = new CellWidget(this, cellSize, r, c, QString(currentGrid->getCell(r, c)->getState()->getLabel().c_str()));
            connect(cellWidgets[r * nbCols + c], &CellWidget::clicked, this, &SimulatorWidget::changeCellState);
            cellWidgets[r * nbCols + c]->setColor(currentGrid->getCell(r, c)->getState()->getColor());
            gridLayout->addWidget(cellWidgets[r * nbCols + c], r, c);
        }
    }
    adjustSize();
}

int SimulatorWidget::getNbRows() const {
    return this->nbRows;
}

Simulator* SimulatorWidget::getSimulator() const{
    return this->simulator;
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
int SimulatorWidget::getCellSize() const {
    return this->cellSize;
}

void SimulatorWidget::changeCellState(int x, int y) {
    Grid* currentGrid = simulator->getIterator().current();
    int newStateID = (currentGrid->getCell(x, y)->getState()->getId() + 1) % (simulator->getAutomata()->getNbStates());
    CellState* newState = simulator->getAutomata()->getAvailableStates()[newStateID];
    currentGrid->getCell(x, y)->setState(newState);

    if (this->simulator->getCurrentGridID() == 0) {
        // Change the start grid if use config the first one
        this->simulator->setStartGrid(new Grid(*currentGrid));
    }
    updateGridDisplay();
}

void SimulatorWidget::setAutomata(int index) {
    this->simulator->setAutomata(AutomataManager::getAutomataManager()->getAutomata(index));
    cleanGrid();
    regenerateEmptyGrid();
    resetGridDisplay();
}

void SimulatorWidget::setBufferSize(int size){
    this->simulator->setBufferSize(size);
}

SimulatorWidget::SimulatorWidget(QWidget* parent, int nbRows, int nbCols, int cellSize) : QWidget(parent) {
    simulator = new Simulator(nullptr, 100);

    this->nbCols = nbCols;
    this->nbRows = nbRows;
    this->cellSize = cellSize;

    initLayout();
    initButtons();
    resetGridDisplay();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SimulatorWidget::btnNextClicked);

    lblCurrentGeneration = new QLabel("Generation #0");

    simulatorLayout->addLayout(gridLayout);
    simulatorLayout->addWidget(lblCurrentGeneration);
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
