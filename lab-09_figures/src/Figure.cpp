#include "Figure.hpp"

Figure::Figure(int id, int x, int y) {
	this->id = id;
	this->x = x;
	this->y = y;
}

Figure::~Figure(){}

void Figure::move(int new_x, int new_y) {
	this->x = new_x;
	this->y = new_y;
}

int Figure::get_id() {
	return this->id;
}

