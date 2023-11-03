#pragma once

#include "Figure.hpp"

class Circle : public Figure {
public:
    Circle(int id, int x, int y, int radius, const char* label);
    ~Circle();

    void print() const;
    void zoom(int factor);
    bool is_inside(int x, int y) const;

private:
    int radius;
    char* label;
};
