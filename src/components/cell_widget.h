#ifndef CELL_WIDGET_H
#define CELL_WIDGET_H

#include <QWidget>
#include <QPalette>

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

  signals:
    void clicked(int x, int y);
};

#endif // CELL_WIDGET_H
