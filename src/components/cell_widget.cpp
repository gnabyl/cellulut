#include "cell_widget.h"
#include <iostream>

CellWidget::CellWidget(QWidget* parent, int cellSize, Cell* cell)
    : QWidget(parent), cell(cell) {

    setFixedSize(cellSize, cellSize);
    setAutoFillBackground(true);

    this->updateDisplay();
}

void CellWidget::updateDisplay() {
    if (cell->getDirection() != none) {
        // TODO: Draw ant
    }
    this->setToolTip(cell->getState()->getLabel().c_str());
    this->setColor(cell->getState()->getColor());
}


void CellWidget::setColor(const QColor& color) {
    QPalette pal = palette();
    pal.setColor(QPalette::Window, color);
    setPalette(pal);
}

void CellWidget::setSize(int size) {
    setFixedSize(size, size);
}

void CellWidget::setCell(Cell *cell) {
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
