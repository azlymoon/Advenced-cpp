#ifndef MATRIX_H
#define MATRIX_H
#include <string>
#include <fstream>
#include <vector>

namespace Matrix {
    class MatrixException : public std::exception {
    private:
        std::string message_;
    public:
        explicit MatrixException(std::string message);
        std::string getMessage() const;
    };

    class Matrix {
    private:
        int n_{}, m_{};
        int tmp_n_{}, tmp_m_{};
        std::vector<std::vector<int>> matrix_{};
        std::vector<std::vector<int>> tmp_matrix_{};
        std::ifstream in_;
    public:
        Matrix();
        ~Matrix();
        void save_changes();
//        void allocate(int n, int m, std::vector<std::vector<int>>& matrix);
//        void clear_matrix(int n, std::vector<std::vector<int>>& matrix);
        void load(const std::string& filename);
        void print();
        void add (Matrix& b);
        void mul (Matrix& b);
        int elem (int row, int col);
    };
}
#endif // MATRIX_H
