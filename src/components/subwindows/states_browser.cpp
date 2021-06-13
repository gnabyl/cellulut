#include "states_browser.h"

StatesBrowser::StatesBrowser(QWidget* parent,std::pair<int,CellState**> statetab) : QDialog(parent),size(statetab.first) {
    mainLayout = new QVBoxLayout(this);

    this->statesTable = statetab.second;

    initStateTable(statetab);
    initButtons();

    mainLayout->addWidget(stateTable);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);
    Createstate = new Create_State(this);


    adjustSize();
}

void StatesBrowser::initStateTable(std::pair<int,CellState**> statetab) {
    int nb = statetab.first;
    stateTable = new QTableWidget(nb, 3, this);
    stateItems = new QTableWidgetItem** [nb];

    stateTable->setHorizontalHeaderLabels(QStringList({"Id", "label", "Color" }));
    stateTable->setSelectionMode(QAbstractItemView::SingleSelection);
    stateTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    for (int i = 0; i<nb; i ++) {
        stateItems[i] = new QTableWidgetItem*[3];
        stateItems[i][0] = new QTableWidgetItem(std::to_string(statetab.second[i]->getId()).c_str());
        stateItems[i][1] = new QTableWidgetItem(statetab.second[i]->getLabel().c_str());
        stateItems[i][2] =  new QTableWidgetItem(statetab.second[i]->getColor().name());

        for (int j = 0; j < 3; j ++) {
            stateTable->setItem(i, j, stateItems[i][j]);
        }
    }

    stateTable->resizeColumnToContents(0);
    stateTable->resizeColumnToContents(1);
    stateTable->resizeColumnToContents(3);
    stateTable->resizeRowsToContents();

    int totalWidth = 20;
    for (int j = 0; j < 3; j ++) {
        totalWidth += stateTable->columnWidth(j);
    }

    stateTable->setFixedWidth(totalWidth);
    stateTable->selectRow(0);
}

void StatesBrowser::initButtons() {
    buttonsLayout = new QHBoxLayout(this);
    btnChoose = new QPushButton("Choose", this);
    btnCreate = new QPushButton("Create", this);
    btnDelete = new QPushButton("Delete", this);
    btnSave = new QPushButton("Save", this);

    buttonsLayout->addWidget(btnChoose);
    buttonsLayout->addWidget(btnCreate);
    buttonsLayout->addWidget(btnDelete);
    buttonsLayout->addWidget(btnSave);




    connect(btnCreate, &QPushButton::clicked, this, &StatesBrowser::openCreateState);
    connect(btnChoose, &QPushButton::clicked, this, &StatesBrowser::chooseState);

}

/*
 *          SLOTS
 */


void StatesBrowser::openCreateState(){
  Createstate->exec();
}


void StatesBrowser::chooseState() {
    if (stateTable->selectionModel()->selectedIndexes().size() > 0) {
        emit stateChanged(this->stateID,statesTable[stateTable->selectionModel()->selectedIndexes().at(0).row()]);
        close();
    }
}

void StatesBrowser::receiveStateID(int id){
    stateID = id;
}

StatesBrowser::~StatesBrowser() {
    for (int i = 0; i < size; i ++) {
        for (int j = 0; j < 3; j ++) {
            delete stateItems[i][j];
        }
        delete[] stateItems[i];
    }
    delete[] stateItems;
}
