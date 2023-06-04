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
        matrix_ = tmp_matrix_;
    }

//    void Matrix::allocate(int n, int m, std::vector<std::vector<int>>& matrix) {
//        try {
//            matrix = new int *[n];
//            for (int i = 0; i < n; i++)
//                matrix[i] = new int[m];
//        } catch (const std::bad_alloc& e) {
//            throw MatrixException("bad_alloc");
//        }
//    }

    void Matrix::load(const std::string& fname) {
        in_.open(fname);
        if (!in_.is_open())
            throw MatrixException("file_error");

        tmp_matrix_.clear();
        in_ >> tmp_n_ >> tmp_m_;
        in_.get();
        std::string line;
        while (std::getline(in_, line)) {
            std::istringstream iss(line);
            std::vector<int> row;
            int num, count = 0;
            while (iss >> num) {
                row.push_back(num);
                count++;
            }
            if (count != tmp_m_)
                throw MatrixException("format_error");
            tmp_matrix_.push_back(row);
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
        if (n_ != b.m_)
            throw MatrixException("dimension_error");

        tmp_matrix_.clear();
        tmp_n_ = n_;
        tmp_m_ = b.m_;

        for (int i = 0; i < n_; i++) {
            std::vector<int> row;
            for (int j = 0; j < b.m_; j++) {
                int sum = 0;
                for (int k = 0; k < n_; k++) {
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



