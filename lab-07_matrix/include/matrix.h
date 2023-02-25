#ifndef LAB_08_MATRIX_H
#define LAB_08_MATRIX_H

#include <cstdio>
#include <cstddef>

class Matrix {
public:
  Matrix(const std::size_t r, const std::size_t c);
  Matrix(const Matrix& m);
  ~Matrix();

  std::size_t get_rows() const;
  std::size_t get_cols() const;
  void set(const std::size_t i, const std::size_t j, const int val);
  int get(const std::size_t i, const std::size_t j) const;
  void print(FILE *f) const;

  Matrix operator+(const Matrix& m) const;
  Matrix operator-(const Matrix& m) const;
  Matrix operator*(const Matrix& m) const;
  
  Matrix& operator=(const Matrix& m);
  Matrix& operator+=(const Matrix& m);
  Matrix& operator-=(const Matrix& m);
  Matrix& operator*=(const Matrix& m);

  bool operator==(const Matrix& m) const;
  bool operator!=(const Matrix& m) const;
private:
  std::size_t _rows;
  std::size_t _cols;
  int **_data;
};

#endif
