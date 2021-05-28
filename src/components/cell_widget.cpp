#include "cell_widget.h"
#include <iostream>

CellWidget::CellWidget(QWidget* parent, int cellSize, Cell* cell)
    : QWidget(parent), cell(cell) {

    setFixedSize(cellSize, cellSize);
    setAutoFillBackground(true);

    this->updateDisplay();
}

void CellWidget::updateDisplay() {
    this->setToolTip(cell->getState()->getLabel().c_str());
    this->setColor(cell->getState()->getColor());
}


void CellWidget::setColor(const QColor& color) {
    QPalette pal = palette();
    pal.setColor(QPalette::Window, color);
    setPalette(pal);
}

void CellWidget::drawAnt(QPainter painter) {
    QRectF rect = this->rect();

    QPainterPath path;
    path.moveTo(rect.left() + (rect.width() / 2.0), rect.top() + rect.height() / 4.0);
    path.lineTo(rect.left() + (rect.width() / 4.0), rect.bottom() - rect.height() / 4.0);
    path.lineTo(rect.right() - (rect.width() / 4.0), rect.bottom() - rect.height() / 4.0);
    path.lineTo(rect.left() + (rect.width() / 2.0), rect.top() + rect.height() / 4.0);

    painter.fillPath(path, QBrush(Qt::red));
}

void CellWidget::paintEvent(QPaintEvent* event) {
    if (cell->getDirection() != none) {
        drawAnt(QPainter(this));
    }
}

void CellWidget::setSize(int size) {
    setFixedSize(size, size);
}

void CellWidget::setCell(Cell* cell) {
    this->cell = cell;
}

Cell* CellWidget::getCell() const {
    return this->cell;
}

void CellWidget::mousePressEvent(QMouseEvent* event) {
    mouseClicked = true;
}

void CellWidget::mouseReleaseEvent(QMouseEvent* event) {
    if (mouseClicked) {
        mouseClicked = false;
        emit clicked(cell->getX(), cell->getY());
    }
}
