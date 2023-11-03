#include "employees.h"
#include <iostream>
#include <fstream>

employees::Employee::Employee(std::string name, int32_t base_salary) {
    _name = name;
    _base_salary = base_salary;
}

employees::Employee::Employee(){
    _name = "";
    _base_salary = 0;
}

std::string employees::Employee::name() {
    return _name;
}

int32_t employees::Employee::base_salary() const {
    return _base_salary;
}

void employees::Employee::set_base_salary(int base_salary) {
    _base_salary = base_salary;
}

void employees::Employee::set_name(std::string name) {
    _name = std::move(name);
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

bool employees::Developer::has_bonus() const {
    return _has_bonus;
}

void employees::Developer::input(std::istream& in) {
    in >> _name >> _base_salary >> _has_bonus;
}

int32_t employees::Developer::type() const {
    return _type;
}

void employees::Developer::output(std::ostream& out) const {
    out << "Developer" << std::endl;
    out << "Name: " << _name << std::endl;
    out << "Base Salary: " << _base_salary << std::endl;
    out << "Has bonus: " << (_has_bonus ? "+" : "-") << std::endl;
}

void employees::Developer::save(const std::string& output_path) const {
    std::ofstream out(output_path, std::ios::out | std::ios::binary);

    out.write((char*)& _type, sizeof(int32_t));
    out.write(_name.c_str(), _name.size());
    out.write("0", sizeof(char));
    out.write((char*)& _base_salary, sizeof(int32_t));
    out.write((char*)& _has_bonus, sizeof(bool));

    out.close();
}

void employees::Developer::load(const std::string &input_path) {
    std::ifstream in(input_path, std::ios::in | std::ios::binary);

    in.read((char*)& _type, sizeof(int32_t));

    char c;
    std::string buf;
    in.read((char*)& c, 1);
    while (c != '0') {
        buf += c;
        in.read((char*)& c, 1);
    }
    set_name(buf);

    in.read((char*)& _base_salary, sizeof(int32_t));
    in.read((char*)& _has_bonus, sizeof(bool));

    in.close();
}

int32_t employees::SalesManager::sold_nm() const {
    return _sold_nm;
}

int32_t employees::SalesManager::price() const {
    return _price;
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

int32_t employees::SalesManager::type() const {
    return _type;
}

void employees::SalesManager::save(const std::string& output_path) const {
    std::ofstream out(output_path, std::ios::out | std::ios::binary);

    out.write((char*)& _type, sizeof(int32_t));
    out.write(_name.c_str(), _name.size());
    out.write((char*)& _base_salary, sizeof(int32_t));
    out.write((char*)& _sold_nm, sizeof(int32_t));
    out.write((char*)& _price, sizeof(int32_t));

    out.close();
}

void employees::SalesManager::load(const std::string &input_path) {
    std::ifstream in(input_path, std::ios::in | std::ios::binary);

    in.read((char*)& _type, sizeof(int32_t));

    char c;
    std::string buf;
    in.read((char*)& c, 1);
    while (c != '0') {
        buf += c;
        in.read((char*)& c, 1);
    }
    set_name(buf);

    in.read((char*)& _base_salary, sizeof(int32_t));
    in.read((char*)& _sold_nm, sizeof(int32_t));
    in.read((char*)& _price, sizeof(int32_t));

    in.close();
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

void employees::EmployeesArray::save(const std::string& output_path) {
    std::ofstream out(output_path, std::ios::binary);
    size_t size = _employees.size();
    out.write((char*)& size, sizeof(int32_t));
    for (size_t i = 0; i < _employees.size(); i++) {
        _employees[i]->save(output_path);
    }
    out.close();
}

void employees::EmployeesArray::load(const std::string &input_path) {
    std::ifstream in(input_path, std::ios::binary);
    int32_t count;
    in.read((char *)& count, sizeof (int32_t));
    for (int i = 0; i < count; i++) {
        int32_t type;
        in.read((char *) &type, sizeof(int32_t));
        if (type == 1) {
            employees::Employee *dev = new Developer();
            dev->load(input_path);
            add(dev);
        } else if (type == 2) {
            employees::Employee *manager = new SalesManager();
            manager->load(input_path);
            add(manager);
        }
    }
    in.close();
}

std::ostream& employees::operator<<(std::ostream& out, const EmployeesArray& arr) {
    for (size_t i = 0; i < arr._employees.size(); i++) {
        out << i + 1 << ". " << *arr._employees[i];
    }
    std::cout << "== Total salary: " << arr.total_salary() << std::endl;;
    return out;
}

