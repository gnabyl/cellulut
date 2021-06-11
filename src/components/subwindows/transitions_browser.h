#ifndef TRANSITIONSBROWSER_H
#define TRANSITIONSBROWSER_H

#include <QDialog>
#include <QPushButton>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include "utils/transition_strategy.h"
#include "utils/database.h"

class TransitionsBrowser : public QDialog{
    Q_OBJECT
    QVBoxLayout* mainLayout;
    QFormLayout* transitionLayout;
    QComboBox* transitionsCbb;
    QPushButton* btnConfirm;

    int nbTransitions = 0;
    TransitionStrategy** transitions = nullptr;
    TransitionStrategy* selectedTransition = nullptr;

    void updateCombobox();

public:
    TransitionsBrowser(QWidget* parent);
    ~TransitionsBrowser();

    void setTransitions(int nbTransitions, TransitionStrategy** transitions);
    void openTransitionBrowser();

signals:
    void transitionChanged(TransitionStrategy* transition);

public slots:
    void chooseTransition();
    void transitionsCbbChanged(int id);

};

#endif // TRANSITIONSBROWSER_H
