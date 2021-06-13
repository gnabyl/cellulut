#ifndef CONFIGSBROWSER_H
#define CONFIGSBROWSER_H

#include <QDialog>
#include <QObject>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QMessageBox>
#include <utility>
#include "../../utils/grid.h"
#include "../../utils/database.h"

class ConfigsBrowser : public QDialog
{
    Q_OBJECT

    QVBoxLayout* mainLayout;
    QHBoxLayout* buttonsLayout;

    QTableWidget* configsTable;
    QTableWidgetItem*** configsItems;

    QPushButton *btnLoad, *btnDelete;

    const int TBL_NB_COLS = 3;

    std::pair<int, Grid**> loadedConfigsInfos;

    void initConfigsTable();
    void initButtons();

  public:
    ConfigsBrowser(QWidget* parent);
    ~ConfigsBrowser();
    void openConfigsBrowser(Automata* automata);

  signals:
    void configChanged(Grid* config);

  private slots:
    void chooseConfig();
};

#endif // CONFIGSBROWSER_H
