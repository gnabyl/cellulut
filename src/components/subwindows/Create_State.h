#ifndef CREATE_STATE_H
#define CREATE_STATE_H

#include <QDialog>
#include <QPushButton>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include "utils/database.h"
#include <QMessageBox>

class Create_State: public QDialog{
    Q_OBJECT
    QVBoxLayout* mainLayout;
    QFormLayout* colorLayout;
    QFormLayout* labelLayout;
    QFormLayout* idLayout;

    QComboBox* StateCbb;
    QLineEdit* label;
    QLineEdit* id;
    QComboBox* colorCbb;

    QPushButton* btnConfirm;


    void updateCombobox();
    void initButtons();

public:
     Create_State(QWidget* parent);


public slots:
   void newState();


};


#endif // CREATE_STATE_H
