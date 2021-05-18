#include "main_window.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    // Window setup
    setWindowTitle("LO21 - CELLULUT - Automate Cellulaire");

    // Components setup
    mainLayout = new QHBoxLayout(this);
    centralWidget = new QWidget(this);

    mainMenuBar = new MenuBar(this);
    simulatorWidget = new SimulatorWidget(this, 5, 5, 50);
    controlPanel = new ControlPanel(this, simulatorWidget);

    // Add components
    mainLayout->addWidget(simulatorWidget);
    mainLayout->addWidget(controlPanel);
    centralWidget->setLayout(mainLayout);

    setMenuBar(mainMenuBar);
    setCentralWidget(centralWidget);

    adjustSize();
}

MainWindow::~MainWindow() {

}
