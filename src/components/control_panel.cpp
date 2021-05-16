#include "control_panel.h"
#include <iostream>

void ControlPanel::setAutomatas() {
    AutomataManager *automataManager = AutomataManager::getAutomataManager();
    // Game Of Life automata
    CellState** golStates = new CellState*[2];
    golStates[0] = new CellState(0, "dead", Qt::white);
    golStates[1] = new CellState(1, "alive", Qt::black);
    Grid* golStartGrid = new Grid(golStates[0], simulatorWidget->width(), simulatorWidget->height());
    automataManager->addAutomata(golStates, new GOLTransition(), new VonNeumannNeighborhood(*golStartGrid), 2, "Game of Life", "Game of Life Automata", "Conway", 1970);
    // Game of Life
    for (int i = 0; i < automataManager->getNbAutomatas(); i ++) {
        automataCbb->addItem(QString(automataManager->getAutomata(i).getName().c_str()));
    }
}

void ControlPanel::initEventHandler() {
    connect(nbRowsSpb, SIGNAL(valueChanged(int)), simulatorWidget, SLOT(setNbRows(int)));
    connect(nbColsSpb, SIGNAL(valueChanged(int)), simulatorWidget, SLOT(setNbCols(int)));
    connect(cellSizeSpb, SIGNAL(valueChanged(int)), simulatorWidget, SLOT(setCellSize(int)));
}

ControlPanel::ControlPanel(QWidget* parent, SimulatorWidget* simulatorWidget) : QWidget(parent), simulatorWidget(simulatorWidget) {
    // Layouts
    automatasLayout = new QFormLayout;
    automataBtnLayout = new QHBoxLayout;
    gridConfigLayout = new QFormLayout;
    mainLayout = new QVBoxLayout(this);

    // Widgets
    automataCbb = new QComboBox(this);
    automataCreateBtn = new QPushButton("Create new", this);
    automataDeleteBtn = new QPushButton("Delete", this);
    automataSaveBtn = new QPushButton("Save", this);
    automataLoadBtn = new QPushButton("Load", this);
    cellSizeSpb = new QSpinBox(this);
    nbRowsSpb = new QSpinBox(this);
    nbColsSpb = new QSpinBox(this);


    // Init data
    setAutomatas();
    nbRowsSpb->setKeyboardTracking(false);
    nbRowsSpb->setValue(20);
    nbRowsSpb->setMaximum(100);
    nbRowsSpb->setMinimum(2);

    nbColsSpb->setKeyboardTracking(false);
    nbColsSpb->setValue(20);
    nbColsSpb->setMaximum(100);
    nbColsSpb->setMinimum(2);

    cellSizeSpb->setKeyboardTracking(false);
    cellSizeSpb->setValue(20);
    cellSizeSpb->setMaximum(50);
    cellSizeSpb->setMinimum(5);

    // Add
    automatasLayout->addRow("Automata", automataCbb);

    automataBtnLayout->addWidget(automataCreateBtn);
    automataBtnLayout->addWidget(automataDeleteBtn);
    automataBtnLayout->addWidget(automataSaveBtn);
    automataBtnLayout->addWidget(automataLoadBtn);


    gridConfigLayout->addRow("Rows Number", nbRowsSpb);
    gridConfigLayout->addRow("Cols Number", nbColsSpb);
    gridConfigLayout->addRow("Cell size", cellSizeSpb);


    mainLayout->addLayout(automatasLayout);
    mainLayout->addLayout(automataBtnLayout);
    mainLayout->addLayout(gridConfigLayout);

    setLayout(mainLayout);

    initEventHandler();

}

ControlPanel::~ControlPanel() {
    delete automatasLayout;
    delete automataBtnLayout;
    delete gridConfigLayout;
}
