#include "Scheme.hpp"

Scheme::Scheme(int capacity) {
	count_ = 0;
	capacity_ = capacity;
	figures_ = new Figure * [capacity];
}

Scheme::~Scheme() {
	for (int i = 0; i < count_; i++)
		delete figures_[i];
	delete[] figures_;
}

void Scheme::push_back_figure(Figure* fg) {
	if (count_ < capacity_) {
		figures_[count_] = fg;
		count_++;
	}
}

Figure* Scheme::find_figure(int id) {
	for (int i = 0; i < count_; i++) {
		if (figures_[i]->get_id() == id)
			return figures_[i];
	}
	return nullptr;
}

void Scheme::remove_figure(int id) {
	int remove_index = -1;
	for (int i = 0; i < count_; i++) {
		if (figures_[i]->get_id() == id)
			remove_index = i;
	}
	delete figures_[remove_index];
	if (remove_index != -1) {
		for (int i = remove_index + 1; i < count_; i++) {
			figures_[i - 1] = figures_[i];
		}
		count_--;
	}
}

void Scheme::print_all_figures() {
	for (int i = 0; i < count_; i++)
		figures_[i]->print();
}

void Scheme::zoom_figure(int id, int factor) {
	this->find_figure(id)->zoom(factor);
}

Figure* Scheme::is_inside_figure(int x, int y) {
	for (int i = 0; i < count_; i++) {
		if (figures_[i]->is_inside(x, y) == true)
			return figures_[i];
	}
	return nullptr;
}

void Scheme::move(int id, int new_x, int new_y) {
	this->find_figure(id)->move(new_x, new_y);
}