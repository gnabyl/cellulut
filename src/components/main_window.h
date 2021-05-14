#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QWidget>
#include <components/menubar.h>
#include <components/simulator_widget.h>
#include <components/control_panel.h>

class MainWindow : public QMainWindow {
    Q_OBJECT
    QWidget* centralWidget;
    QHBoxLayout* mainLayout;
    MenuBar* mainMenuBar;
    SimulatorWidget* simulatorWidget;
    ControlPanel* controlPanel;
  public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  signals:

};

#endif // MAIN_WINDOW_H
