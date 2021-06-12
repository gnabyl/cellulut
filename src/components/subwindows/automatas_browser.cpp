#include "automatas_browser.h"

AutomatasCreator::AutomatasCreator(QWidget* parent) : QDialog(parent), nbStates(0),chosenNeighborhood(nullptr), chosenTransition(nullptr), chosenStates(nullptr), chosenName(QString("")){
    transitionsBrowser = new TransitionsBrowser(this);
    neighborsBrowser = new NeighborsBrowser(this);

    mainLayout = new QVBoxLayout(this);
    fieldsLayout = new QFormLayout(this);
    initStatesBrowser();

    nameField = new QLineEdit(this);
    nbStatesSpb = new QSpinBox(this);
    statesList = new QListWidget(this);
    statesItems = new QListWidgetItem*;
    editStateButton = new QPushButton(this);
    editStateButton->setText("Edit selected state");
    editStateButton->setDisabled(true);
    neighborhoodChooseButton = new QPushButton(this);
    transitionChooseButton = new QPushButton(this);

    neighborhoodChooseButton->setText("Browse");
    transitionChooseButton->setText("Browse");

    fieldsLayout->addRow("Automaton name : ",nameField);
    fieldsLayout->addRow("Number of states : ",nbStatesSpb);
    fieldsLayout->addRow("States : ",statesList);
    fieldsLayout->addRow(editStateButton);
    fieldsLayout->addRow("Neighborhood : ",neighborhoodChooseButton);
    fieldsLayout->addRow("Transition rule : ",transitionChooseButton);

    mainLayout->addLayout(fieldsLayout);

    validateButton = new QPushButton(this);
    validateButton->setText("Validate");
    validateButton->setDisabled(true);

    mainLayout->addWidget(validateButton);

    initEvents();
}

void AutomatasCreator::initStatesBrowser(){
    try{
        DBManager dbMan = DBManager::getDB();
        std::pair<int,CellState**> statetab=dbMan.loadStatesfromDB();
        statesBrowser = new StatesBrowser(this,statetab);
    }

    catch(DBException e){
        QMessageBox window;
        window.setText(QString::fromStdString(e.getInfo()));
        window.open();
    }

    connect(statesBrowser,SIGNAL(stateChanged(int,CellState*)),this,SLOT(setChosenState(int,CellState*)));
}

void AutomatasCreator::initEvents(){
    connect(transitionChooseButton,&QPushButton::clicked,transitionsBrowser,&TransitionsBrowser::openTransitionBrowser);
    connect(neighborhoodChooseButton,&QPushButton::clicked,neighborsBrowser,&NeighborsBrowser::openNeighborsBrowser);
    connect(transitionsBrowser,&TransitionsBrowser::transitionChanged,this,&AutomatasCreator::receiveTransition);
    connect(neighborsBrowser,&NeighborsBrowser::neighborChanged,this,&AutomatasCreator::receiveNeighborhood);
    connect(validateButton,&QPushButton::clicked,this,&AutomatasCreator::startCreation);
    connect(nameField,&QLineEdit::textChanged,this,&AutomatasCreator::setChosenName);
    connect(nbStatesSpb,SIGNAL(valueChanged(int)),this,SLOT(changeNbStates(int)));
    connect(statesList,SIGNAL(currentRowChanged(int)),this,SLOT(allowEditing(int)));
    connect(statesList,SIGNAL(currentRowChanged(int)),statesBrowser,SLOT(receiveStateID(int)));
    connect(editStateButton,&QPushButton::clicked,statesBrowser,&StatesBrowser::exec);
}

void AutomatasCreator::receiveTransition(TransitionStrategy* t){
    this->chosenTransition = t;
    this->validateButton->setDisabled(false);
}

void AutomatasCreator::receiveNeighborhood(NeighborhoodStrategy* n){
    this->chosenNeighborhood = n;
}

void AutomatasCreator::allowEditing(int nb){
    this->editStateButton->setDisabled(false);
}

void AutomatasCreator::updateStatesList(){
    while(statesList->count()>0){
      statesList->takeItem(0);
    }
    for (int i = 0; i < nbStates; i ++) {
        CellState* s = chosenStates[i];
        std::string item = std::to_string(s->getId());
        item += ". " + s->getLabel();
        statesList->addItem(item.c_str());
    }
    statesList->adjustSize();
}

void AutomatasCreator::setChosenName(const QString& s){
    this->chosenName = s;
}

void AutomatasCreator::setChosenState(int id, CellState *c){
    chosenStates[id] = c;
    updateStatesList();
}

void AutomatasCreator::startCreation(){
    try{
        createAutomaton();
    }

    catch(AutomatonCreationException e){
        QMessageBox window;
        window.setText(e.getInfo().c_str());
        window.show();
    }
}

void AutomatasCreator::createAutomaton(){
    if(chosenNeighborhood == nullptr || chosenTransition == nullptr || nbStates == 0)
        throw AutomatonCreationException("Not enough information was given to create a new automaton !");
    else{
        DBManager dbMan = DBManager::getDB();
        dbMan.insertAutomataIntoDB(chosenName,nbStates,chosenTransition->getName().c_str(),chosenNeighborhood->getName().c_str(),chosenStates);
    }
}

void AutomatasCreator::changeNbStates(int nb){
    if(nb>8){
        nbStatesSpb->setValue(8);
        QMessageBox window;
        window.setText("You cannot create an automaton with more than 8 states !");
        window.show();
    }
    else{
        //Change states table in the back
        CellState** newTab = new CellState*[nb];
        if(nbStates != 0){
            for(size_t i=0; i<this->nbStates;i++)
                newTab[i] = chosenStates[i];
            delete[] chosenStates;
        }
        this->chosenStates = newTab;

        //Refresh states list
        QListWidgetItem** newTabBis = new QListWidgetItem*[nb];
        if(nbStates != 0){
            for(size_t i=0;i<this->nbStates;i++)
                newTabBis[i] = statesItems[i];
        }
        statesItems = newTabBis;
        statesItems[nb] = new QListWidgetItem(this->statesList);
        statesItems[nb]->setText("Void state");

        this->nbStates = nb;
    }
}

AutomatasBrowser::AutomatasBrowser(QWidget* parent) : QDialog(parent) {
    mainLayout = new QVBoxLayout(this);
    automataCreator = new AutomatasCreator(this);

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

    automatasTable->setHorizontalHeaderLabels(QStringList({"Name", "Author", "Description", "Number of states"}));
    automatasTable->setSelectionMode(QAbstractItemView::SingleSelection);
    automatasTable->setSelectionBehavior(QAbstractItemView::SelectRows);
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
    connect(btnCreate,&QPushButton::clicked,this,&AutomatasBrowser::openAutomataCreator);
}

void AutomatasBrowser::openAutomatasBrowser() {
    AutomataManager* automataManager = AutomataManager::getAutomataManager();
    // Clean current table
    if (automatasItems) {
        for (int r = 0; r < automataManager->getNbAutomatas(); r ++) {
            for (int c = 0; c < TBL_NB_COLS; c ++) {
                delete automatasItems[r][c];
            }
            delete[] automatasItems[r];
            automatasItems[r] = nullptr;
        }
        delete[] automatasItems;
        automatasItems = nullptr;
    }

    try{
        DBManager dbMan = DBManager::getDB();
        AutomataManager::getAutomataManager()->clear();
        dbMan.loadAutomatasFromDB();
    }
    catch(DBException e){
        QMessageBox window;
        window.setText(QString::fromStdString(e.getInfo()));
        window.open();
    }
    automatasTable->setRowCount(automataManager->getNbAutomatas());

    automatasItems = new QTableWidgetItem** [automataManager->getNbAutomatas()];
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

    open();
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

void AutomatasBrowser::openAutomataCreator(){
    automataCreator->exec();
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
