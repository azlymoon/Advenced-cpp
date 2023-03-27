#include "Circle.hpp"
#include <iostream>
#include <cmath>

Circle::Circle(int id, int x, int y, int radius, const char* label) : Figure(id, x, y) {
	this->radius = radius;
	this->label = label;
}

void Circle::print() const {
	std::cout << "Circle " << this->id << ": "
		<< "x = " << this->x
		<< " y = " << this->y
		<< " radius = " << this->radius
		<< " label = " << this->label << std::endl;
}

void Circle::zoom(int factor) {
	this->radius *= factor;
}

bool Circle::is_inside(int x, int y) const {
	return (std::pow(this->x - x, 2) + std::pow(this->y - y, 2) <= std::pow(radius, 2));
}