
#ifndef LO21_CELLSTATE_H
#define LO21_CELLSTATE_H
enum color{blue, red, yellow, pink, cyan , green, orange, purple};


class Cellstate{

public:
void setid(int i);
void seetlabel(std::string s);
void setcolor(color c);
int getid() const;
color getcolor() const;
std::string getlabel()const;
Cellstate(int x, std::string l,color c):id(x),label(l),color(c);

private:
    int id;
    std::string label;
    color color;
};

#endif //LO21_CELLSTATE_H
