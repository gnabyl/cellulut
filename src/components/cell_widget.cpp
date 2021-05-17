#include "cell_widget.h"

CellWidget::CellWidget(QWidget* parent, int cellSize, QString label) : QWidget(parent), label(label) {
    setFixedSize(cellSize, cellSize);
    setAutoFillBackground(true);
}


void CellWidget::setColor(const QColor& color) {
    QPalette pal = palette();
    pal.setColor(QPalette::Background, color);
    setPalette(pal);
}
