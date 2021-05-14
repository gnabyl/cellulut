#include "cell_widget.h"

CellWidget::CellWidget(QWidget *parent, int cellSize) : QWidget(parent)
{
    setFixedSize(cellSize, cellSize);
    setAutoFillBackground(true);
    setColor(Qt::white);
}


void CellWidget::setColor(const QColor &color) {
    QPalette pal = palette();
    pal.setColor(QPalette::Background, color);
    setPalette(pal);
}
