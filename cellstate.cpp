#include "cellstate.h"

void CellState::setId(int i){
    this->id=i;
}
void CellState::setLabel(std::string s){
    this->label=s;
}

void CellState::setColor(color c){
    this->color=c;
}
int CellState::getId(){
    return this->id;
}
color CellState::getColor(){
    return this->color;
}
std::string CellState::getLabel(){
    return this->label
}
