#ifndef CELLWIDGET_H
#define CELLWIDGET_H

#include <QWidget>
#include <QPalette>

class CellWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CellWidget()=default;
    explicit CellWidget(QWidget *parent, int cellSize);
    void setColor(const QColor &color);

signals:

};

#endif // CELLWIDGET_H
