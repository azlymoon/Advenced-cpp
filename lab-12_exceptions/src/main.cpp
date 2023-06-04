#include "matrix.h"
#include <string>
#include <iostream>
#include <memory>

int read_reg() {
    std::string reg;
    std::cin >> reg;
    reg = reg.substr(1, 1);
    return std::stoi(reg);
}

int main() {
    std::string r;
    std::string command;
    std::unique_ptr<Matrix::Matrix[]> registers(new Matrix::Matrix[10]);
    std::cin >> command;
    while (command != "exit") {
        if (command == "load") {
            std::string fname;
            int reg = read_reg();
            std::cin >> fname;
            try {
                registers[reg].load(fname);
            } catch (const Matrix::MatrixException& e) {
                if (e.getMessage() == "file_error")
                    std::cout << "LOAD: unable to open file." << std::endl;
                else if (e.getMessage() == "format_error")
                    std::cout << "LOAD: invalid file format." << std::endl;
            }
        }
        else if (command == "print") {
            int reg = read_reg();
            registers[reg].print();
        }
        else if (command == "add") {
            int reg1 = read_reg();
            int reg2 = read_reg();
            try {
                registers[reg1].add(registers[reg2]);
            } catch (const Matrix::MatrixException& e) {
                std::cout << "ADD: dimensions do not match." << std::endl;
            }
        }
        else if (command == "mul") {
            int reg1 = read_reg();
            int reg2 = read_reg();
            try {
                registers[reg1].mul(registers[reg2]);
            } catch (const Matrix::MatrixException& e) {
                std::cout << "MUL: #arg1.columns != #arg2.rows." << std::endl;
            }
        }
        else if (command == "elem") {
            try {
                int row, col;
                int reg = read_reg();
                std::cin >> row >> col;
                std::cout << registers[reg].elem(row, col) << std::endl;
            } catch (const Matrix::MatrixException& e) {
                std::cout << "ACCESS: bad index." << std::endl;
            }
        }
        std::cin >> command;
    }

    return 0;
}