#ifndef LO21_CELLSTATE_H
#define LO21_CELLSTATE_H

#include <QColor>
#include <string>

enum color {blue, red, yellow, pink, cyan, green, orange, purple};
enum direction {up, down, left, right,none};


class CellState {
  public:
    void setId(int i);
    void setLabel(std::string s);
    void setColor(QColor c);
    void setDirection(direction d);
    direction getDirection() const;
    int getId() const;
    QColor getColor() const;
    std::string getLabel() const;
    CellState(int x, std::string l, QColor c,direction d=none): id(x), label(l), col(c), dir(d) {}

  private:
    int id;
    std::string label;
    QColor col;
    direction dir;
};

/*
class CellStateDirection: public CellState {
private:
 direction dir;
public:
 CellStateDirection(int x, std::string l, QColor c,direction direction=none): CellState(x,l,c),dir(direction){}
 direction getDirection() const;
 void setDirection(direction d);

};
*/


#endif //LO21_CELLSTATE_H
