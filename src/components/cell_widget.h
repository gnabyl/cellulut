#ifndef CELL_WIDGET_H
#define CELL_WIDGET_H

#include <QWidget>
#include <QPalette>
#include <QMouseEvent>
#include <QToolTip>
#include "utils/cell.h"

class CellWidget : public QWidget {
    Q_OBJECT
  public:
    explicit CellWidget() = default;
    explicit CellWidget(QWidget* parent, int cellSize, Cell* cell);
    void setColor(const QColor& color);
    void setSize(int size);
    void setCell(Cell* cell);
    Cell* getCell() const;
    void updateDisplay();

  private:
    Cell* cell;
    bool mouseClicked = false;

  protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

  signals:
    void clicked(int x, int y);
};

#endif // CELL_WIDGET_H
