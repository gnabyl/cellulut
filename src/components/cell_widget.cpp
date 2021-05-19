#include "cell_widget.h"

CellWidget::CellWidget(QWidget* parent, int cellSize, int x, int y, QString label) : QWidget(parent), label(label), x(x), y(y) {
    setFixedSize(cellSize, cellSize);
    setAutoFillBackground(true);
}


void CellWidget::setColor(const QColor& color) {
    QPalette pal = palette();
    pal.setColor(QPalette::Window, color);
    setPalette(pal);
}

void CellWidget::setSize(int size) {
    setFixedSize(size, size);
}
