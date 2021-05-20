#ifndef LO21_CELLSTATE_H
#define LO21_CELLSTATE_H

#include <QColor>
#include <string>

enum color {blue, red, yellow, pink, cyan, green, orange, purple};


class CellState {
  public:
    void setId(int i);
    void setLabel(std::string s);
    void setColor(QColor c);
    int getId() const;
    QColor getColor() const;
    std::string getLabel() const;
    CellState(int x, std::string l, QColor c): id(x), label(l), col(c) {}

  private:
    int id;
    std::string label;
    QColor col;
};

#endif //LO21_CELLSTATE_H
