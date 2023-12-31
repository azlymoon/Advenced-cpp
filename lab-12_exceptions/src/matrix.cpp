#ifndef MATRIX_CPP
#define MATRIX_CPP
#include <utility>
#include <iostream>
#include <sstream>
#include "matrix.h"

namespace Matrix {
    MatrixException::MatrixException(std::string message) :
            message_(std::move(message)) {}

    std::string MatrixException::getMessage() const { return message_; }

    Matrix::Matrix() = default;

    Matrix::~Matrix() {
        in_.close();
    }

    void Matrix::save_changes() {
        n_ = tmp_n_;
        m_ = tmp_m_;
        matrix_ = std::move(tmp_matrix_);

    }

    void Matrix::load(const std::string& filename) {
        in_.open(filename);
        if (!in_.is_open())
            throw MatrixException("file_error");

        tmp_matrix_.clear();
        tmp_n_ = 0, tmp_m_ = 0;
        if (!(in_ >> tmp_n_ >> tmp_m_)) {
            in_.close();
            throw MatrixException("format_error");
        }
        in_.get();

        std::string line;
        int count_n = 0;
        while (std::getline(in_, line)) {
            std::istringstream iss(line);
            std::vector<int> row;
            int num, count_m = 0;
            while (iss >> num) {
                row.push_back(num);
                count_m++;
            }
            if (count_m != tmp_m_) {
                in_.close();
                throw MatrixException("format_error");
            }
            tmp_matrix_.push_back(row);
            count_n++;
        }
        if (count_n != tmp_n_) {
            in_.close();
            throw MatrixException("format_error");
        }
        in_.close();
        save_changes();
    }

    void Matrix::print() {
        for (int i = 0; i < n_; i++) {
            for (int j = 0; j < m_ - 1; j++) {
                std::cout << matrix_[i][j] << ' ';
            }
            std::cout << matrix_[i][m_ - 1] << std::endl;
        }
    }

    void Matrix::add(Matrix &b) {
        if (n_ != b.n_ || m_ != b.m_)
            throw MatrixException("dimension_error");

        for (int i = 0; i < n_; i++) {
            for (int j = 0; j < m_; j++) {
                matrix_[i][j] += b.matrix_[i][j];
            }
        }
    }

    void Matrix::mul(Matrix &b) {
        if (m_ != b.n_)
            throw MatrixException("dimension_error");

        tmp_matrix_.clear();
        tmp_n_ = n_, tmp_m_ = b.m_;

        for (int i = 0; i < n_; i++) {
            std::vector<int> row;
            for (int j = 0; j < b.m_; j++) {
                int sum = 0;
                for (int k = 0; k < m_; k++) {
                    sum += matrix_[i][k] * b.matrix_[k][j];
                }
                row.push_back(sum);
            }
            tmp_matrix_.push_back(row);
        }

        save_changes();
    }

    int Matrix::elem(int row, int col) {
        if (row < 0 || row >= n_ || col < 0 || col >= m_)
            throw MatrixException("index_error");

        return matrix_[row][col];
    }
}

#endif // MATRIX_CPP



