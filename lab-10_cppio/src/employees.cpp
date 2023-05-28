#include "employees.h"
#include <iostream>

employees::Employee::Employee(std::string name, int32_t base_salary) {
    _name = name;
    _base_salary = base_salary;
}

employees::Employee::Employee(){
    _name = "";
    _base_salary = 0;
}

void employees::Employee::set_base_salary(int base_salary) {
    _base_salary = base_salary;
}

void employees::Employee::set_name(std::string name) {
    _name = name;
}

std::istream& employees::operator>>(std::istream& in, Employee& e) {
    e.input(in);
    return in;
}

std::ostream& employees::operator<<(std::ostream& out, const Employee& e) {
    e.output(out);
    return out;
}



int employees::Developer::salary() const {
    int salary = _base_salary;
    if (_has_bonus) { salary += 1000; }
    return salary;
}

employees::Developer::Developer(
    std::string name,
    int32_t base_salary, 
    bool has_bonus
) : Employee(name, base_salary){
    _has_bonus = has_bonus;
}

void employees::Developer::set_has_bonus(bool has_bonus) {
    _has_bonus = has_bonus;
}

employees::Developer::Developer() : Employee(){
    _has_bonus = 0;
}

void employees::Developer::input(std::istream& in) {
    in >> _name >> _base_salary >> _has_bonus;
}

void employees::Developer::output(std::ostream& out) const {
    out << "Developer" << std::endl;
    out << "Name: " << _name << std::endl;
    out << "Base Salary: " << _base_salary << std::endl;
    out << "Has bonus: " << (_has_bonus ? "+" : "-") << std::endl;
}



int employees::SalesManager::salary() const {
    return _base_salary + _sold_nm * _price * 0.01;
}

employees::SalesManager::SalesManager(
    std::string name,
    int32_t base_salary,
    int32_t sold_nm,
    int32_t price
) : Employee(name, base_salary) {
    _sold_nm = sold_nm;
    _price = price;
}

employees::SalesManager::SalesManager() : Employee() {
    _sold_nm = 0;
    _price = 0;
}

void employees::SalesManager::set_price(int price) {
    _price = price;
}

void employees::SalesManager::set_sold_nm(int sold_nm) {
    _sold_nm = sold_nm;
}

void employees::SalesManager::input(std::istream& in) {
    in >> _name >> _base_salary >> _sold_nm >> _price;
}

void employees::SalesManager::output(std::ostream& out) const {
    out << "Sales Manager" << std::endl;
    out << "Name: " << _name << std::endl;
    out << "Base Salary: " << _base_salary << std::endl;
    out << "Sold items: " << _sold_nm << std::endl;
    out << "Item price: " << _price << std::endl;
}



void employees::EmployeesArray::add(const Employee* e) {
    _employees.push_back(e);
}

int32_t employees::EmployeesArray::total_salary() const {
    int32_t total_salary = 0;
    for (size_t i = 0; i < _employees.size(); i++)
        total_salary += _employees[i]->salary();
    return total_salary;
}

std::ostream& employees::operator<<(std::ostream& out, const EmployeesArray& arr) {
    for (size_t i = 0; i < arr._employees.size(); i++) {
        out << i + 1 << ". " << *arr._employees[i];
    }
    std::cout << "== Total salary: " << arr.total_salary() << std::endl;;
    return out;
}