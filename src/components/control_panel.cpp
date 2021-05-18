#include "control_panel.h"
#include <iostream>

/*
 * Pseudo function for loading automatas
 * It should load automatas from database
 */
void ControlPanel::loadAutomatas() {
    AutomataManager* automataManager = AutomataManager::getAutomataManager();
    // Game Of Life automata
    CellState** golStates = new CellState*[2];
    golStates[0] = new CellState(0, "dead", Qt::white);
    golStates[1] = new CellState(1, "alive", Qt::black);
    Grid* golStartGrid = new Grid(golStates[0], simulatorWidget->getNbCols(), simulatorWidget->getNbRows());
    automataManager->addAutomata(golStates, new GOLTransition(), new MooreNeighborhood(golStartGrid), 2,
                                 "Game of Life", "Game of Life Automata", "Conway", 1970);
    // Brian's Brain automata
    CellState** bbStates = new CellState*[3];
    bbStates[0] = new CellState(0, "off", Qt::white);
    bbStates[1] = new CellState(1, "dying", Qt::blue);
    bbStates[2] = new CellState(2, "on", Qt::black);
    Grid* bbStartGrid = new Grid(bbStates[0], simulatorWidget->getNbCols(), simulatorWidget->getNbRows());
    automataManager->addAutomata(bbStates, new BBTransition(), new MooreNeighborhood(bbStartGrid), 3,
                                 "Brian's Brain", "Brian's Brain Automata", "Brian Silverman", 1996);
    for (int i = 0; i < automataManager->getNbAutomatas(); i ++) {
        automataCbb->addItem(QString(automataManager->getAutomata(i)->getName().c_str()));
    }
}

void ControlPanel::initEventHandler() {
    connect(nbRowsSpb, SIGNAL(valueChanged(int)), simulatorWidget, SLOT(setNbRows(int)));
    connect(nbColsSpb, SIGNAL(valueChanged(int)), simulatorWidget, SLOT(setNbCols(int)));
    connect(cellSizeSpb, SIGNAL(valueChanged(int)), simulatorWidget, SLOT(setCellSize(int)));
    connect(automataCbb, SIGNAL(currentIndexChanged(int)), simulatorWidget, SLOT(setAutomata(int)));
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

    initEventHandler();

    // Init data
    loadAutomatas();
    nbRowsSpb->setKeyboardTracking(false);
    nbRowsSpb->setValue(simulatorWidget->getNbRows());
    nbRowsSpb->setMaximum(100);
    nbRowsSpb->setMinimum(2);

    nbColsSpb->setKeyboardTracking(false);
    nbColsSpb->setValue(simulatorWidget->getNbCols());
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
}

ControlPanel::~ControlPanel() {
    delete automatasLayout;
    delete automataBtnLayout;
    delete gridConfigLayout;
}
