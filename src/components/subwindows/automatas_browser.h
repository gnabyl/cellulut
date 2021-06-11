#ifndef AUTOMATASBROWSER_H
#define AUTOMATASBROWSER_H

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QFormLayout>
#include <QSpinBox>
#include "../../utils/automata_manager.h"
#include "../../utils/database.h"
#include "transitions_browser.h"
#include "neighbors_browser.h"

class AutomatasCreator : public QDialog{

    TransitionsBrowser* transitionsBrowser;
    NeighborsBrowser* neighborsBrowser;

    QVBoxLayout* mainLayout;
    QFormLayout* fieldsLayout;

    QLineEdit* nameField;
    QSpinBox* nbStatesSpb;
    QPushButton* neighborhoodChooseButton;
    QPushButton* transitionChooseButton;

    QPushButton* validateButton;

    void initButtons();
public:
    AutomatasCreator(QWidget* parent);
};

class AutomatasBrowser : public QDialog {
    Q_OBJECT

    QVBoxLayout* mainLayout;
    QHBoxLayout* buttonsLayout;

    QTableWidget* automatasTable;
    QTableWidgetItem*** automatasItems;

    QPushButton *btnChoose, *btnCreate, *btnDelete, *btnSave;

    AutomatasCreator* automataCreator;

    const int TBL_NB_COLS = 4;

    void initAutomatasTable();
    void initButtons();

  public:
    AutomatasBrowser(QWidget* parent);
    ~AutomatasBrowser();

  signals:
    void automataChanged(int id);
    void btnCreateClicked();

  private slots:
    void chooseAutomata();
    void openAutomataCreator();
};

#endif // AUTOMATASBROWSER_H
