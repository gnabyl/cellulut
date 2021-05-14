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
}

void SimulatorWidget::updateGrid() {
    // TODO: Show cells
    gridLayout->setAlignment(Qt::AlignCenter);
    gridLayout->setSpacing(2);
    cellWidgets = new CellWidget*[nbRows * nbCols];
    for (int r = 0; r < nbRows; r ++) {
        for (int c = 0; c < nbCols; c ++) {
            cellWidgets[r * nbCols + c] = new CellWidget(this, cellSize);
            gridLayout->addWidget(cellWidgets[r * nbCols + c], r, c);
        }
    }
    adjustSize();
}

void SimulatorWidget::setNbRows(int nbRows) {
    cleanGrid();
    this->nbRows = nbRows;
    updateGrid();
}
void SimulatorWidget::setNbCols(int nbCols) {
    cleanGrid();
    this->nbCols = nbCols;
    updateGrid();
}
void SimulatorWidget::setCellSize(int size) {
    cleanGrid();
    this->cellSize = size;
    updateGrid();
}

SimulatorWidget::SimulatorWidget(QWidget* parent, int nbRows, int nbCols, int cellSize) : QWidget(parent) {
    this->nbCols = nbCols;
    this->nbRows = nbRows;
    this->cellSize = cellSize;

    initLayout();
    initButtons();
    updateGrid();

    simulatorLayout->addLayout(gridLayout);
    simulatorLayout->addLayout(controllerLayout);

    setLayout(simulatorLayout);

    adjustSize();
}

void SimulatorWidget::cleanGrid() {
    for (int r = 0; r < nbRows; r ++) {
        for (int c = 0; c < nbCols; c ++) {
            gridLayout->removeWidget(cellWidgets[r * nbCols + c]);
        }
    }
    for (int i = 0; i < nbRows * nbCols; i ++) {
        delete cellWidgets[i];
    }
    delete [] cellWidgets;
}

SimulatorWidget::~SimulatorWidget() {
    cleanGrid();
}
