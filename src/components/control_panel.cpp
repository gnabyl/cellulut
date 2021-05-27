#include "control_panel.h"
#include <iostream>
#include <string>
/*
 * Pseudo function for loading automatas
 * It should load automatas from database
 */



void ControlPanel::neighborhoodSetting(){
    NeighborsBrowseWindow* neigborhoodsWindow= new NeighborsBrowseWindow;
    neigborhoodsWindow->show();
}


void ControlPanel::stateSettings(){
    StateBrowseWindow* stateWindow= new StateBrowseWindow;
    stateWindow ->show();
}
void ControlPanel::transitionSetting(){
    TransitionBrowseWindow* transition= new TransitionBrowseWindow;
    transition->show();
}


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
    connect(bufferSizeSpb, SIGNAL(valueChanged(int)), simulatorWidget, SLOT(setBufferSize(int)));
    connect(automataCbb, SIGNAL(currentIndexChanged(int)), this, SLOT(setAutomata(int)));
    connect(automataCbb, SIGNAL(currentIndexChanged(int)), simulatorWidget, SLOT(setAutomata(int)));
    connect(sliderSpeed, SIGNAL(valueChanged(int)), simulatorWidget, SLOT(changeFrequency(int)));
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
    cellSizeSpb->setValue(simulatorWidget->getCellSize());
    cellSizeSpb->setMaximum(50);
    cellSizeSpb->setMinimum(5);

    //Creation of the boxes layout
    gridSettingsLayout = new QFormLayout(gridSettingsBox);
    gridSettingsLayout->addRow("Rows number", nbRowsSpb);
    gridSettingsLayout->addRow("Cols number", nbColsSpb);
    gridSettingsLayout->addRow("Cell size", cellSizeSpb);
}

void ControlPanel::initAutomataSettings(){
    automataSettingsLayout = new QVBoxLayout(automataSettingsBox);

    //Choose automata
    automataLabel = new QLabel("Automata",automataSettingsBox);
    btnBrowseAutomatas = new QPushButton(tr("Browse..."), automataSettingsBox);
    textAutomataName = new QLineEdit(automataSettingsBox);
    automataFieldLayout = new QHBoxLayout(automataSettingsBox);
    automataFieldLayout->addWidget(automataLabel);
    automataFieldLayout->addWidget(textAutomataName);
    automataFieldLayout->addWidget(btnBrowseAutomatas);
    automataSettingsLayout->addLayout(automataFieldLayout);

    //Choose state x8
    statesLabels = new QLabel*[8];
    btnBrowseStates = new QPushButton*[8];
    textStatesNames = new QLineEdit*[8];
    statesFieldLayout = new QHBoxLayout*[8];
    for(int i=0; i<8; i++){
        char num = i+49;
        statesLabels[i] = new QLabel(automataSettingsBox);
        statesLabels[i]->setText(QString("State ").append(QString(num)));
        btnBrowseStates[i] = new QPushButton(automataSettingsBox);
        btnBrowseStates[i]->setText(tr("Browse..."));
        textStatesNames[i] = new QLineEdit(automataSettingsBox);
        statesFieldLayout[i] = new QHBoxLayout(automataSettingsBox);
        statesFieldLayout[i]->addWidget(statesLabels[i]);
        statesFieldLayout[i]->addWidget(textStatesNames[i]);
        statesFieldLayout[i]->addWidget(btnBrowseStates[i]);
        automataSettingsLayout->addLayout(statesFieldLayout[i]);
        connect(btnBrowseStates[i], SIGNAL(clicked()), this, SLOT(stateSettings()));

   }

    //Choose neighborhood
    neighborhoodLabel = new QLabel(automataSettingsBox);
    neighborhoodLabel->setText("Neighborhood");
    textNeighborhoodName = new QLineEdit(automataSettingsBox);
    btnBrowseNeighborhoods = new QPushButton(automataSettingsBox);
    btnBrowseNeighborhoods->setText(tr("Browse..."));
    neighborhoodFieldLayout = new QHBoxLayout(automataSettingsBox);
    neighborhoodFieldLayout->addWidget(neighborhoodLabel);
    neighborhoodFieldLayout->addWidget(textNeighborhoodName);
    neighborhoodFieldLayout->addWidget(btnBrowseNeighborhoods);
    automataSettingsLayout->addLayout(neighborhoodFieldLayout);
    connect(btnBrowseNeighborhoods, SIGNAL(clicked()), this, SLOT(neighborhoodSetting()));

    //Choose transition rule
    ruleLabel = new QLabel(automataSettingsBox);
    ruleLabel->setText("Transition rule");
    textRuleName = new QLineEdit(automataSettingsBox);
    btnBrowseRules = new QPushButton(automataSettingsBox);
    btnBrowseRules->setText(tr("Browse..."));
    ruleFieldLayout = new QHBoxLayout(automataSettingsBox);
    ruleFieldLayout->addWidget(ruleLabel);
    ruleFieldLayout->addWidget(textRuleName);
    ruleFieldLayout->addWidget(btnBrowseRules);
    automataSettingsLayout->addLayout(ruleFieldLayout);
    connect(btnBrowseRules, SIGNAL(clicked()), this, SLOT(transitionSetting()));

}

void ControlPanel::initRunSettings(){
    runSettingsLayout = new QFormLayout(runSettingsBox);

    sliderSpeed = new BSlider(Qt::Horizontal, runSettingsBox);
    sliderSpeed->setValue(simulatorWidget->getFrequency());
    sliderSpeed->setMinimum(simulatorWidget->getFrequency());
    sliderSpeed->setMaximum(10);
    runSettingsLayout->addRow("Execution speed",sliderSpeed);

    bufferSizeSpb = new QSpinBox(runSettingsBox);
    bufferSizeSpb->setKeyboardTracking(false);
    bufferSizeSpb->setValue(simulatorWidget->getSimulator()->getBufferSize());
    bufferSizeSpb->setMaximum(500);
    bufferSizeSpb->setMinimum(2);
    runSettingsLayout->addRow("Buffer size",bufferSizeSpb);
}

ControlPanel::~ControlPanel() {
    delete automatasLayout;
    delete gridSettingsLayout;
}

void ControlPanel::setAutomata(int id) {
    textAutomataName->setText(QString::fromStdString(AutomataManager::getAutomataManager()->getAutomata(id)->getName()));
    textNeighborhoodName->setText(QString::fromStdString(AutomataManager::getAutomataManager()->getAutomata(id)->getNeighborhoodStrategy()->getName()));
    textRuleName->setText(QString::fromStdString(AutomataManager::getAutomataManager()->getAutomata(id)->getTransitionStrategy()->getName()));
}
