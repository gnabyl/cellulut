#include "cell_state.h"

void CellState::setId(int i) {
    this->id = i;
}
void CellState::setLabel(std::string s) {
    this->label = s;
}

void CellState::setCol(color c) {
    this->col = c;
}
int CellState::getId() const {
    return this->id;
}
QColor CellState::getCol() const {
    return this->col;
}
std::string CellState::getLabel() const {
    return this->label;
}
