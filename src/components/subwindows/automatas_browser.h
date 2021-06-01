#ifndef AUTOMATASBROWSER_H
#define AUTOMATASBROWSER_H

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include "../../utils/automata_manager.h"

class AutomatasBrowser : public QDialog {
    Q_OBJECT

    QVBoxLayout* mainLayout;
    QHBoxLayout* buttonsLayout;

    QTableWidget* automatasTable;
    QTableWidgetItem*** automatasItems;

    QPushButton *btnChoose, *btnCreate, *btnDelete, *btnSave;

    const int TBL_NB_COLS = 4;

    void initAutomatasTable();
    void initButtons();

  public:
    AutomatasBrowser(QWidget* parent);
    ~AutomatasBrowser();
};

#endif // AUTOMATASBROWSER_H
