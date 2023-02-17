#include "my_vector.hpp"
using namespace std;

MyVector::MyVector() {
	this->_capacity = 2;
	this->_size = 0;
	this->_data = new int[this->_capacity];
	for (size_t i = 0; i < this->_capacity; i++)
		this->_data[i] = 0;
}

MyVector::MyVector(size_t init_capacity) {
	this->_capacity = init_capacity;
	this->_size = 0;
	this->_data = new int[this->_capacity];
	for (size_t i = 0; i < this->_capacity; i++)
		this->_data[i] = 0;
}

void MyVector::set(size_t index, int value) {
	this->_data[index] = value;
}

int MyVector::get(size_t index) {
	return this->_data[index];
}

size_t MyVector::size() {
	return this->_size;
}

size_t MyVector::capacity() {
	return this->_capacity;
}

void MyVector::push_back(int value) {
	if (this->_size == this->_capacity) {
		int* tmp_data = new int[this->_capacity * 2];
		for (size_t i = 0; i < this->_size; i++)
			tmp_data[i] = this->_data[i];
		delete this->_data;
		this->_data = tmp_data;
		this->_capacity *= 2;
	}

	this->_data[this->_size] = value;
	this->_size++;
}

void MyVector::insert(size_t index, int value) {
	if (this->_size == this->_capacity) {
		int* tmp_data = new int[this->_capacity * 2];
		for (size_t i = 0; i < this->_size; i++)
			tmp_data[i] = this->_data[i];
		delete this->_data;
		this->_data = tmp_data;
		this->_capacity *= 2;
	}

	for (size_t i = this->_size; i > index; i--) {
		this->_data[i] = this->_data[i - 1];
	}

	this->_data[index] = value;
	this->_size++;
}

void MyVector::erase(size_t index) {
	for (size_t i = index; i < this->_size; i++) {
		this->_data[i] = this->_data[i + 1];
	}
	this->_size--;
}

void MyVector::reserve(size_t new_capacity) {
	if (new_capacity > this->_capacity) {
		int* tmp_data = new int[new_capacity];
		for (size_t i = 0; i < this->_size; i++)
			tmp_data[i] = this->_data[i];
		delete this->_data;
		this->_data = tmp_data;
		this->_capacity = new_capacity;
	}
}

void MyVector::resize(size_t new_size) {
	if (new_size > this->_capacity) {
		size_t new_capacity = (new_size > this->_capacity * 2 ? new_size : this->_capacity * 2);
		int* tmp_data = new int[new_capacity];
		for (size_t i = 0; i < this->_size; i++)
			tmp_data[i] = this->_data[i];
		delete this->_data;
		this->_data = tmp_data;
		this->_capacity = new_capacity;

		for (size_t i = this->_size; i < new_size; i++)
			this->_data[i] = 0;
	}
	this->_size = new_size;
}

MyVector::~MyVector() {
	delete[] this->_data;
}