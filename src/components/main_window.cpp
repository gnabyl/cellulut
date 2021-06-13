#include "main_window.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    // Window setup
    setWindowTitle("LO21 - CELLULUT - Automate Cellulaire");

    // Components setup
    mainLayout = new QHBoxLayout(this);
    centralWidget = new QWidget(this);

<<<<<<< HEAD

=======
>>>>>>> 71b7d0c37c55bdfbac72ac3105c5100b9e03be73
    simulatorWidget = new SimulatorWidget(this, 20, 20, 20);
    controlPanel = new ControlPanel(this, simulatorWidget);

    // Add components
    mainLayout->addWidget(simulatorWidget);
    mainLayout->addWidget(controlPanel);
    centralWidget->setLayout(mainLayout);

<<<<<<< HEAD

=======
>>>>>>> 71b7d0c37c55bdfbac72ac3105c5100b9e03be73
    setCentralWidget(centralWidget);

    adjustSize();
}

MainWindow::~MainWindow() {

}
