#ifndef CELL_WIDGET_H
#define CELL_WIDGET_H

#include <QWidget>
#include <QPalette>
#include <QMouseEvent>
#include <QToolTip>

class CellWidget : public QWidget {
    Q_OBJECT
  public:
    explicit CellWidget() = default;
    explicit CellWidget(QWidget* parent, int cellSize, int x, int y, QString label = QString(""));
    void setColor(const QColor& color);
    void setSize(int size);

  private:
    QString label;
    int x, y;
    bool mouseClicked = false;

  protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

  signals:
    void clicked(int x, int y);
};

#endif // CELL_WIDGET_H
