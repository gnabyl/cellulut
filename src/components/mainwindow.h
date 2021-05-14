#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QWidget>
#include <components/menubar.h>
#include <components/simulatorwidget.h>
#include <components/controlpanel.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QWidget *centralWidget;
    QHBoxLayout *mainLayout;
    MenuBar *mainMenuBar;
    SimulatorWidget *simulatorWidget;
    ControlPanel *controlPanel;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:

};

#endif // MAINWINDOW_H
