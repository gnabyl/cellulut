#include "control_panel.h"
#include <iostream>
#include <string>

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
    for (int i = 0; i < automataManager->getNbAutomatas(); i ++) {
        automataCbb->addItem(QString(automataManager->getAutomata(i)->getName().c_str()));
    }
}

void ControlPanel::initEventHandler() {
    connect(nbRowsSpb, SIGNAL(valueChanged(int)), simulatorWidget, SLOT(setNbRows(int)));
    connect(nbColsSpb, SIGNAL(valueChanged(int)), simulatorWidget, SLOT(setNbCols(int)));
    connect(cellSizeSpb, SIGNAL(valueChanged(int)), simulatorWidget, SLOT(setCellSize(int)));
    //connect(automataCbb, SIGNAL(currentIndexChanged(int)), simulatorWidget, SLOT(setAutomata(int)));
    connect(bufferSizeSpb, SIGNAL(valueChanged(int)), simulatorWidget, SLOT(setBufferSize(int)));
    connect(automataCbb, SIGNAL(currentIndexChanged(int)), textAutomataName, SLOT(setAutomataName(int)));
    connect(textAutomataName, SIGNAL(automataChanged(int)), simulatorWidget, SLOT(setAutomata(int)));
}

ControlPanel::ControlPanel(QWidget* parent, SimulatorWidget* simulatorWidget) : QWidget(parent), simulatorWidget(simulatorWidget) {
    mainLayout = new QVBoxLayout(this);

    //Automata spinbox
    automataCbb = new QComboBox(this);
    automatasLayout = new QFormLayout;
    automatasLayout->addRow("Automata", automataCbb);
    mainLayout->addLayout(automatasLayout);

    // 1 : grid settings
    gridSettingsBox = new QGroupBox(tr("Grid settings"));
    initGridSettings();
    mainLayout->addWidget(gridSettingsBox);

    //2 : automata settings
    automataSettingsBox = new QGroupBox(tr("Automata settings"));
    initAutomataSettings();
    mainLayout->addWidget(automataSettingsBox);

    //3 : run settings
    runSettingsBox = new QGroupBox(tr("Run settings"));
    initRunSettings();
    mainLayout->addWidget(runSettingsBox);

    initEventHandler();
    //Init automatas
    loadAutomatas();

    setLayout(mainLayout);
}

void ControlPanel::initGridSettings(){
    //Creation of the boxes widget
    nbRowsSpb = new QSpinBox(gridSettingsBox);
    nbColsSpb = new QSpinBox(gridSettingsBox);
    cellSizeSpb = new QSpinBox(gridSettingsBox);

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

    //Creation of the boxes layout
    gridSettingsLayout = new QVBoxLayout(gridSettingsBox);

    nbRowsLayout = new QFormLayout(gridSettingsBox);
    nbRowsLayout->addRow("Rows number : ", nbRowsSpb);

    nbColsLayout = new QFormLayout(gridSettingsBox);
    nbColsLayout->addRow("Cols number : ", nbColsSpb);

    cellSizeLayout = new QFormLayout(gridSettingsBox);
    cellSizeLayout->addRow("Cell size : ", cellSizeSpb);

    gridSettingsLayout->addLayout(nbRowsLayout);
    gridSettingsLayout->addLayout(nbColsLayout);
    gridSettingsLayout->addLayout(cellSizeLayout);
}

void ControlPanel::initAutomataSettings(){
    automataSettingsLayout = new QVBoxLayout(automataSettingsBox);

    //Choose automata
    automataLabel = new QLabel("Automata",automataSettingsBox);
    btnBrowseAutomatas = new QPushButton(automataSettingsBox);
    btnBrowseAutomatas->setText(tr("Browse..."));
    textAutomataName = new AutomataNameBox(automataSettingsBox);
    automataFieldLayout = new QHBoxLayout(automataSettingsBox);
    automataFieldLayout->addWidget(automataLabel);
    automataFieldLayout->addWidget(textAutomataName);
    automataFieldLayout->addWidget(btnBrowseAutomatas);
    automataSettingsLayout->addLayout(automataFieldLayout);

    //Choose state x8
    btnBrowseStates = new QPushButton*[8];
    statesFieldLayout = new QFormLayout*[8];
    for(int i=0; i<8; i++){
        char num = i+49;
        btnBrowseStates[i] = new QPushButton(automataSettingsBox);
        btnBrowseStates[i]->setText(tr("Browse..."));
        statesFieldLayout[i] = new QFormLayout(automataSettingsBox);
        statesFieldLayout[i]->addRow(QString("State ").append(QString(num)),btnBrowseStates[i]);
        automataSettingsLayout->addLayout(statesFieldLayout[i]);
   }

    //Choose neighborhood
    btnBrowseNeighborhoods = new QPushButton(automataSettingsBox);
    btnBrowseNeighborhoods->setText(tr("Browse..."));
    neighborhoodFieldLayout = new QFormLayout(automataSettingsBox);
    neighborhoodFieldLayout->addRow("Neighborhood",btnBrowseNeighborhoods);
    automataSettingsLayout->addLayout(neighborhoodFieldLayout);

    //Choose transition rule
    btnBrowseRules = new QPushButton(automataSettingsBox);
    btnBrowseRules->setText(tr("Browse..."));
    ruleFieldLayout = new QFormLayout(automataSettingsBox);
    ruleFieldLayout->addRow("Transition rule", btnBrowseRules);
    automataSettingsLayout->addLayout(ruleFieldLayout);
}

void ControlPanel::initRunSettings(){
    runSettingsLayout = new QVBoxLayout(runSettingsBox);

    sliderSpeed = new QSlider(Qt::Horizontal,runSettingsBox);
    sliderSpeedLayout = new QFormLayout(runSettingsBox);
    sliderSpeedLayout->addRow("Execution speed",sliderSpeed);
    runSettingsLayout->addLayout(sliderSpeedLayout);

    bufferSizeSpb = new QSpinBox(runSettingsBox);
    bufferSizeSpb->setKeyboardTracking(false);
    bufferSizeSpb->setValue(simulatorWidget->getSimulator()->getBufferSize());
    bufferSizeSpb->setMaximum(100);
    bufferSizeSpb->setMinimum(2);
    bufferSizeFieldLayout = new QFormLayout(runSettingsBox);
    bufferSizeFieldLayout->addRow("Buffer size",bufferSizeSpb);
    runSettingsLayout->addLayout(bufferSizeFieldLayout);
}

void ControlPanel::changeAutomataName(int id){
    if(id==-1) textAutomataName->setText("Personnalisé");
    else
        textAutomataName->setText(QString::fromStdString(AutomataManager::getAutomataManager()->getAutomata(id)->getName().c_str()));

}

ControlPanel::~ControlPanel() {
    delete automatasLayout;
    delete gridSettingsLayout;
}

void AutomataNameBox::setAutomataName(int id){
    if(id==-1)
        setText("Personnalisé");
    else
        setText(QString::fromStdString(AutomataManager::getAutomataManager()->getAutomata(id)->getName()));
    emit automataChanged(id);
}
