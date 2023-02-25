#include "matrix.h"

Matrix::Matrix(std::size_t r, std::size_t c) {
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

void Matrix::print(FILE* f) const {
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < _cols - 1; j++) {
			fprintf(f, "%d ", _data[i][j]);
		}
		fprintf(f, "%d\n", _data[i][_cols - 1]);
	}
}

Matrix& Matrix::operator=(Matrix& m) {
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

bool Matrix::operator!=(Matrix& m) {
	return !(*this == m);
}

Matrix& Matrix::operator+=(Matrix& m) {
	Matrix res = *this + m;
	*this = res;
	return *this;
}

Matrix& Matrix::operator-=(Matrix& m) {
	Matrix res = *this - m;
	*this = res;
	return *this;
}

Matrix& Matrix::operator*=(Matrix& m) {
	Matrix res = *this * m;
	*this = res;
	return *this;
}

Matrix Matrix::operator+(Matrix& m) {
	Matrix res = Matrix(_rows, _cols);
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < _cols; j++) {
			res._data[i][j] = _data[i][j] + m._data[i][j];
		}
	}
	return res;
}

Matrix Matrix::operator-(Matrix& m) {
	Matrix res = Matrix(this->_rows, this->_cols);
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < _cols; j++) {
			res._data[i][j] = _data[i][j] - m._data[i][j];
		}
	}
	return res;
}

Matrix Matrix::operator*(Matrix& m) {
	Matrix res = Matrix(_rows, m._cols);
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < m._cols; j++) {
			for (std::size_t k = 0; k < _cols; k++) {
				res._data[i][j] += _data[i][k] * m._data[k][j];
			}
		}
	}
	return res;
}
