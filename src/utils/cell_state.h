#ifndef LO21_CELLSTATE_H
#define LO21_CELLSTATE_H

#include <string>

enum color {blue, red, yellow, pink, cyan, green, orange, purple};


class CellState {
  public:
    void setId(int i);
    void setLabel(std::string s);
    void setCol(color c);
    int getId() const;
    color getCol() const;
    std::string getLabel() const;
    CellState(int x, std::string l, color c): id(x), label(l), col(c) {}

  private:
    int id;
    std::string label;
    color col;
};

#endif //LO21_CELLSTATE_H
