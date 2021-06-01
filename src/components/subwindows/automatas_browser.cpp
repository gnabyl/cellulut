#include "automatas_browser.h"

AutomatasBrowser::AutomatasBrowser(QWidget* parent) : QDialog(parent) {
    mainLayout = new QVBoxLayout(this);

    initAutomatasTable();
    initButtons();

    mainLayout->addWidget(automatasTable);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);

    adjustSize();
}

void AutomatasBrowser::initAutomatasTable() {
    AutomataManager* automataManager = AutomataManager::getAutomataManager();

    automatasTable = new QTableWidget(automataManager->getNbAutomatas(), TBL_NB_COLS, this);
    automatasItems = new QTableWidgetItem** [automataManager->getNbAutomatas()];

    automatasTable->setHorizontalHeaderLabels(QStringList({"Name", "Author", "Description", "Number of states"}));
    automatasTable->setSelectionMode(QAbstractItemView::SingleSelection);
    automatasTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    for (int i = 0; i < automataManager->getNbAutomatas(); i ++) {
        automatasItems[i] = new QTableWidgetItem*[TBL_NB_COLS];
        automatasItems[i][0] = new QTableWidgetItem(automataManager->getAutomata(i)->getName().c_str());
        automatasItems[i][1] = new QTableWidgetItem(automataManager->getAutomata(i)->getAuthor().c_str());
        automatasItems[i][2] = new QTableWidgetItem(automataManager->getAutomata(i)->getDescription().c_str());
        automatasItems[i][3] = new QTableWidgetItem(std::to_string(automataManager->getAutomata(i)->getNbStates()).c_str());

        for (int j = 0; j < TBL_NB_COLS; j ++) {
            automatasTable->setItem(i, j, automatasItems[i][j]);
        }
    }

    automatasTable->resizeColumnToContents(0);
    automatasTable->resizeColumnToContents(1);
    automatasTable->resizeColumnToContents(3);
    automatasTable->resizeRowsToContents();

    int totalWidth = 20;
    for (int j = 0; j < TBL_NB_COLS; j ++) {
        totalWidth += automatasTable->columnWidth(j);
    }

    automatasTable->setFixedWidth(totalWidth);
    automatasTable->selectRow(0);
}

void AutomatasBrowser::initButtons() {
    buttonsLayout = new QHBoxLayout(this);
    btnChoose = new QPushButton("Choose", this);
    btnCreate = new QPushButton("Create", this);
    btnDelete = new QPushButton("Delete", this);
    btnSave = new QPushButton("Save", this);

    buttonsLayout->addWidget(btnChoose);
    buttonsLayout->addWidget(btnCreate);
    buttonsLayout->addWidget(btnDelete);
    buttonsLayout->addWidget(btnSave);


    connect(btnChoose, &QPushButton::clicked, this, &AutomatasBrowser::chooseAutomata);
}

/*
 *          SLOTS
 */
void AutomatasBrowser::chooseAutomata() {
    if (automatasTable->selectionModel()->selectedIndexes().size() > 0) {
        emit automataChanged(automatasTable->selectionModel()->selectedIndexes().at(0).row());
        close();
    }
}


AutomatasBrowser::~AutomatasBrowser() {
    AutomataManager* automataManager = AutomataManager::getAutomataManager();
    for (int i = 0; i < automataManager->getNbAutomatas(); i ++) {
        for (int j = 0; j < TBL_NB_COLS; j ++) {
            delete automatasItems[i][j];
        }
        delete[] automatasItems[i];
    }
    delete[] automatasItems;
}
