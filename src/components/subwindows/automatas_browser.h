#ifndef AUTOMATASBROWSER_H
#define AUTOMATASBROWSER_H

#include <QString>
#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QFormLayout>
#include <QSpinBox>
#include <QListWidget>
#include "../../utils/automata_manager.h"
#include "../../utils/database.h"
#include "transitions_browser.h"
#include "neighbors_browser.h"
#include "states_browser.h"

class AutomatonCreationException{
    std::string info;

public:
    AutomatonCreationException(std::string s) : info(s){}
        std::string getInfo() const{return info;}
};

class AutomatasCreator : public QDialog{

    Q_OBJECT

    TransitionsBrowser* transitionsBrowser;
    NeighborsBrowser* neighborsBrowser;
    StatesBrowser* statesBrowser;

    QString chosenName;
    int nbStates;
    CellState** chosenStates;
    TransitionStrategy* chosenTransition;
    NeighborhoodStrategy* chosenNeighborhood;

    QVBoxLayout* mainLayout;
    QFormLayout* fieldsLayout;

    QLineEdit* nameField;
    QSpinBox* nbStatesSpb;
    QListWidget* statesList;
    QListWidgetItem** statesItems;
    QPushButton* editStateButton;
    QPushButton* neighborhoodChooseButton;
    QPushButton* transitionChooseButton;

    QPushButton* validateButton;

    void initEvents();
    void createAutomaton();
    void initStatesBrowser();
    void updateStatesList();
public:
    AutomatasCreator(QWidget* parent);

public slots:
    void receiveTransition(TransitionStrategy* t);
    void receiveNeighborhood(NeighborhoodStrategy* n);
    void startCreation();
    void setChosenName(const QString& s);
    void setChosenState(int id,CellState* c);
    void changeNbStates(int nb);
     void allowEditing(int id);
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
    void openAutomatasBrowser();

  signals:
    void automataChanged(int id);
    void btnCreateClicked();

  private slots:
    void chooseAutomata();
    void openAutomataCreator();
};

#endif // AUTOMATASBROWSER_H
