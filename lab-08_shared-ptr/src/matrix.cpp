#include "matrix.hpp"

Matrix::Matrix(const std::size_t r, const std::size_t c) {
	_rows = r;
	_cols = c;
	_data = new int* [r];
	for (std::size_t i = 0; i < _rows; i++) {
		_data[i] = new int[_cols];
		for (std::size_t j = 0; j < _cols; j++) {
			_data[i][j] = 0;
		}
	}
}

Matrix::Matrix(const Matrix& m) {
	_rows = m.get_rows();
	_cols = m.get_cols();
	_data = new int* [_rows];
	for (std::size_t i = 0; i < _rows; i++) {
		_data[i] = new int[_cols];
	}
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < _cols; j++) {
			_data[i][j] = m._data[i][j];
		}
	}
}

Matrix::~Matrix() {
	for (std::size_t i = 0; i < _rows; i++)
		delete[] _data[i];
	delete[] _data;
}

std::size_t Matrix::get_rows() const { return _rows; }
std::size_t Matrix::get_cols() const { return _cols; }

void Matrix::set(const std::size_t i, const std::size_t j, const int val) {
	_data[i][j] = val;
}

int Matrix::get(const std::size_t i, const std::size_t j) const {
	return _data[i][j];
}

Matrix& Matrix::operator=(const Matrix& m) {
	if (&m == this)
		return *this;

	for (std::size_t i = 0; i < _rows; i++)
		delete[] _data[i];
	delete[] _data;
	_rows = m.get_rows();
	_cols = m.get_cols();
	_data = new int* [_rows];
	for (std::size_t i = 0; i < _rows; i++) {
		_data[i] = new int [_cols];
	}
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < _cols; j++) {
			_data[i][j] = m._data[i][j];
		}
	}
	return *this;
}

bool Matrix::operator==(const Matrix& m) const {
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < _cols; j++) {
			if (_data[i][j] != m._data[i][j])
				return false;
		}
	}
	return true;
}

bool Matrix::operator!=(const Matrix& m) const {
	return !(*this == m);
}
