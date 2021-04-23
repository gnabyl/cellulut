#include cellstate.h
void Cellstate::setid(int i ){
    this->id=i;
}
void Cellstate::setlabel(std::string s){
    this->label=s;
}

void Cellstate::setcolor(color c){
    this->color=c;
}
int Cellstate::getid(){
    return this->id;
}
color Cellstate::getcolor(){
    return this->color;
}
std::string Cellstate::getlabel(){
    return this->label
}