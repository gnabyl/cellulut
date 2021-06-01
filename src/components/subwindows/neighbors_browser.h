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
#include <QVariant>
#include "utils/neighborhood_strategy.h"

class NeighborsBrowser : public QDialog{
    Q_OBJECT
    QVBoxLayout* mainLayout;
    QFormLayout* neighborhoodLayout;
    QComboBox* neighborhoodCbb;
    QSpinBox* radius;

    int nbNeighbors = 0;
    NeighborhoodStrategy** neighbors;

    void updateCombobox();

public:
    NeighborsBrowser(QWidget* parent);
    ~NeighborsBrowser();

    void setNeighborhoods(int nbNeighbors, NeighborhoodStrategy** neighbors);


private slots:
//    void clickedactions(int indexItem);

};

#endif // NEIGHBORHOODSBROWSER_H
