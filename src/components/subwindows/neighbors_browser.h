#ifndef NEIGHBORHOODSBROWSER_H
#define NEIGHBORHOODSBROWSER_H

#include <QDialog>
#include <QPushButton>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include "utils/neighborhood_strategy.h"
#include "utils/helpers.h"
#include "utils/database.h"

class NeighborsBrowser : public QDialog{
    Q_OBJECT
    QVBoxLayout* mainLayout;
    QFormLayout* neighborhoodLayout;
    QComboBox* neighborhoodCbb;
    QSpinBox* spbRadius;
    QPushButton* btnConfirm;

    int nbNeighbors = 0;
    NeighborhoodStrategy** neighbors = nullptr;
    NeighborhoodStrategy* selectedNeighbor = nullptr;

    void updateCombobox();

public:
    NeighborsBrowser(QWidget* parent);
    ~NeighborsBrowser();

    void setNeighborhoods(int nbNeighbors, NeighborhoodStrategy** neighbors);

signals:
    void neighborChanged(NeighborhoodStrategy* neighbor);

public slots:
    void chooseNeighbor();
    void neighborCbbChanged(int id);
    void openNeighborsBrowser();

};

#endif // NEIGHBORHOODSBROWSER_H
