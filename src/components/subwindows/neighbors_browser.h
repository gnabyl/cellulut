#ifndef NEIGHBORHOODSBROWSER_H
#define NEIGHBORHOODSBROWSER_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include "utils/database.h"
#include "utils/neighborhood_strategy.h"
#include "utils/helpers.h"

class NeighborCreator : public QDialog {
    Q_OBJECT

    int width, height, centerR, centerC;

    QLineEdit* txtName;
    QGridLayout* gridLayout;
    QVBoxLayout* mainLayout;
    QHBoxLayout* buttonsLayout;
    QFormLayout* infoLayout;
    QCheckBox*** cellsCheckbox;

    QPushButton* btnCreate;

public:
    NeighborCreator(QWidget* parent, int width, int height);
    ~NeighborCreator();
private slots:
    void createNeighbor();
};

class NeighborsBrowser : public QDialog{
    Q_OBJECT
    QVBoxLayout* mainLayout;
    QHBoxLayout* buttonsLayout;
    QFormLayout* neighborhoodLayout;
    QComboBox* neighborhoodCbb;
    QSpinBox* spbRadius;
    QPushButton* btnConfirm;
    QPushButton* btnCreate;

    NeighborCreator* neighborCreator;

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

private slots:
    void openNeighborCreator();

};

#endif // NEIGHBORHOODSBROWSER_H
