#ifndef CELL_WIDGET_H
#define CELL_WIDGET_H

#include <QWidget>
#include <QPalette>

class CellWidget : public QWidget {
    Q_OBJECT
  public:
    explicit CellWidget() = default;
    explicit CellWidget(QWidget* parent, int cellSize);
    void setColor(const QColor& color);

  signals:

};

#endif // CELL_WIDGET_H
