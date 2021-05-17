#ifndef CELL_WIDGET_H
#define CELL_WIDGET_H

#include <QWidget>
#include <QPalette>

class CellWidget : public QWidget {
    Q_OBJECT
  public:
    explicit CellWidget() = default;
    explicit CellWidget(QWidget* parent, int cellSize, QString label = QString(""));
    void setColor(const QColor& color);

  private:
    QString label;

  signals:

};

#endif // CELL_WIDGET_H
