
#ifndef LO21_CELLSTATE_H
#define LO21_CELLSTATE_H
enum color{blue, red, yellow, pink, cyan , green, orange, purple};


class CellState{
public:
    void setId(int i);
    void setLabel(std::string s);
    void setColor(color c);
    int getId() const;
    color getColor() const;
    std::string getLabel()const;
    CellState(int x, std::string l,color c):id(x),label(l),color(c);

private:
        int id;
        std::string label;
        color color;
};

#endif //LO21_CELLSTATE_H
