#ifndef STATES_BROWSER_H
#define STATES_BROWSER_H

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include "../../utils/automata_manager.h"
#include "Create_State.h"
#include "utils/database.h"

class StatesBrowser : public QDialog {
    Q_OBJECT

    CellState** statesTable;

    QVBoxLayout* mainLayout;
    QHBoxLayout* buttonsLayout;
    Create_State*  Createstate;
    QTableWidget* stateTable;
    QTableWidgetItem*** stateItems;
    int size;
    int stateID; //The number of the ID that has to be changed in the current automaton.

    QPushButton *btnChoose, *btnCreate, *btnDelete, *btnSave;

    const int TBL_NB_COLS = 4;

    void initStateTable(std::pair<int,CellState**>);
    void initButtons();
    void completeTable(std::pair<int,CellState**> statetab);

  public:
    StatesBrowser(QWidget* parent,std::pair<int,CellState**>);
    ~StatesBrowser();

  signals:
    void stateChanged(int,CellState*);

  public slots:
    void loadStates();
    void receiveStateID(int id);
  private slots:
    void chooseState();
    void openCreateState();
};



#endif // STATES_BROWSER_H
