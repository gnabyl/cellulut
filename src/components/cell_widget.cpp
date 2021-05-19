#include "cell_widget.h"

CellWidget::CellWidget(QWidget* parent, int cellSize, int x, int y, QString label) : QWidget(parent), label(label), x(x), y(y) {
    setFixedSize(cellSize, cellSize);
    setAutoFillBackground(true);
    this->setToolTip(label);
}


void CellWidget::setColor(const QColor& color) {
    QPalette pal = palette();
    pal.setColor(QPalette::Window, color);
    setPalette(pal);
}

void CellWidget::setSize(int size) {
    setFixedSize(size, size);
}

void CellWidget::mousePressEvent(QMouseEvent *event) {
    mouseClicked = true;
}

void CellWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (mouseClicked) {
        mouseClicked = false;
        emit clicked(x, y);
    }
}
