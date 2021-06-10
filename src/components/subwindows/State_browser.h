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

    QVBoxLayout* mainLayout;
    QHBoxLayout* buttonsLayout;

    QTableWidget* stateTable;
    QTableWidgetItem*** stateItems;
    int size;

    QPushButton *btnChoose, *btnCreate, *btnDelete, *btnSave;

    const int TBL_NB_COLS = 4;

    void initStateTable(std::pair<int,CellState**>);
    void initButtons();

  public:
    StateBrowser(QWidget* parent,std::pair<int,CellState**>);
    ~StateBrowser();

  signals:
    void stateChanged(int id);

  private slots:
    void chooseState();
};



#endif // STATE_BROWSER_H
