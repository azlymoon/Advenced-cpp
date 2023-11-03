#include "Rectangle.hpp"
#include <stdio.h>

Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure(id, x, y){
	this->width = width;
	this->height = height;
}

void Rectangle::print() const {
	printf(
		"Rectangle %d: x = %d y = %d width = %d height = %d\n",
		this->id,
		this->x,
		this->y,
		this->width,
		this->height
	);
}

void Rectangle::zoom(int factor) {
	this->width *= factor;
	this->height *= factor;
}

bool Rectangle::is_inside(int x, int y) const {
	return (
		(this->x - width / 2 <= x && x <= this->x + width / 2) &&
		(this->y - height / 2 <= y && y <= this->y + height / 2)
	);
}