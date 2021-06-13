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
#include <QMessageBox>
#include <QCheckBox>
#include "utils/database.h"
#include "utils/neighborhood_strategy.h"
#include "utils/helpers.h"
#include "utils/database.h"

class NeighborCreator : public QDialog {
    Q_OBJECT

    int width, height, centerR, centerC;

    QLineEdit* txtName;
    QSpinBox* spbRadius;
    QComboBox* neighborsTypeCbb;
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
    void changeNeighborType(int id);
    void changeRadius(int val);
};

class NeighborsBrowser : public QDialog{
    Q_OBJECT
    QVBoxLayout* mainLayout = nullptr;
    QHBoxLayout* buttonsLayout = nullptr;
    QFormLayout* neighborhoodLayout = nullptr;
    QComboBox* neighborhoodCbb = nullptr;
    QSpinBox* spbRadius = nullptr;
    QPushButton* btnConfirm = nullptr;
    QPushButton* btnCreate = nullptr;

    NeighborCreator* neighborCreator = nullptr;

    int nbNeighbors = 0;
    NeighborhoodStrategy** neighbors = nullptr;
    NeighborhoodStrategy* selectedNeighbor = nullptr;

    void updateCombobox();

public:
    NeighborsBrowser(QWidget* parent, int width = 31, int height = 31);
    ~NeighborsBrowser();

    void setNeighborhoods(int nbNeighbors, NeighborhoodStrategy** neighbors);

signals:
    void neighborChanged(NeighborhoodStrategy* neighbor);

public slots:
    void chooseNeighbor();
    void neighborCbbChanged(int id);
    void openNeighborsBrowser();

private slots:
    void openNeighborCreator();

};

#endif // NEIGHBORHOODSBROWSER_H
