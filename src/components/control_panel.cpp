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
    automataManager->addAutomata(golStates, new GOLTransition(), new MooreNeighborhoodGeneralized(1), 2,
                                 "Game of Life", "Game of Life Automata", "Conway", 1970);
    // Brian's Brain automata
    CellState** bbStates = new CellState*[3];
    bbStates[0] = new CellState(0, "off", Qt::white);
    bbStates[1] = new CellState(1, "dying", Qt::blue);
    bbStates[2] = new CellState(2, "on", Qt::black);
    automataManager->addAutomata(bbStates, new BBTransition(), new MooreNeighborhood(), 3,
                                 "Brian's Brain", "Brian's Brain Automata", "Brian Silverman", 1996);


    // David griffeath automata
    CellState** dgStates = new CellState*[4];
    dgStates[0] = new CellState(0, "y", Qt::yellow);
    dgStates[1] = new CellState(1, "c", Qt::cyan);
    dgStates[2] = new CellState(2, "dc", Qt::darkCyan);
    dgStates[3] = new CellState(3, "r", Qt::red);
    automataManager->addAutomata(dgStates, new DGTransition(), new MooreNeighborhood(), 4,
                                 "L’automate circulaire de Griffeath", "Griffeath Ciruclar Automata", "David Griffeath", 1);
    //(jaune), 1 (orange clair),2 (orange foncé), 3 (rouge)

    // Langton Loop automata
    CellState** llStates = new CellState*[8];
    llStates[0] = new CellState(0, "y", Qt::yellow);
    llStates[1] = new CellState(1, "c", Qt::cyan);
    llStates[2] = new CellState(2, "dc", Qt::darkCyan);
    llStates[3] = new CellState(3, "r", Qt::red);
    llStates[4] = new CellState(4, "b", Qt::blue);
    llStates[5] = new CellState(5, "g", Qt::green);
    llStates[6] = new CellState(6, "m", Qt::magenta);
    llStates[7] = new CellState(7, "dg", Qt::darkGray);

    automataManager->addAutomata(llStates, new LLTransition(), new VonNeumannNeighborhood(), 8,
                                 "Langton Loop", "Langton Loop Automata", "Christopher Langton", 1984);

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
