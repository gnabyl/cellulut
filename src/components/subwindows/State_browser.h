#ifndef STATE_BROWSER_H
#define STATE_BROWSER_H

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include "../../utils/automata_manager.h"

class StateBrowser : public QDialog {
    Q_OBJECT

    CellState** statesTable;

    QVBoxLayout* mainLayout;
    QHBoxLayout* buttonsLayout;

    QTableWidget* stateTable;
    QTableWidgetItem*** stateItems;
    int size;
    int stateID; //The number of the ID that has to be changed in the current automaton.

    QPushButton *btnChoose, *btnCreate, *btnDelete, *btnSave;

    const int TBL_NB_COLS = 4;

    void initStateTable(std::pair<int,CellState**>);
    void initButtons();

  public:
    StateBrowser(QWidget* parent,std::pair<int,CellState**>);
    ~StateBrowser();

  signals:
    void stateChanged(int,CellState*);

  public slots:
    void receiveStateID(int id);

  private slots:
    void chooseState();
};



#endif // STATE_BROWSER_H
