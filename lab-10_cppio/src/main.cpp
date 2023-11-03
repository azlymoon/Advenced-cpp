#include <iostream>
#include "employees.h"

int main() {
	std::string command;
	employees::EmployeesArray arr;
	while (true) {
		std::cin >> command;
		if (command == "load") {
            std::string input;
            std::cin >> input;
            arr.load(input);
		}
		else if (command == "save") {
            std::string out;
            std::cin >> out;
            arr.save(out);
		}
		else if (command == "add") {
			int type;
			std::string name;
			int32_t base_salary;
			std::cin >> type;
			if (type == 1) {
				bool has_bonus;
				std::cin >> name >> base_salary >> has_bonus;
				employees::Developer* d = new employees::Developer(name, base_salary, has_bonus);
				arr.add(d);
			}
			else if (type == 2) {
				int32_t sold_nm, price;
				std::cin >> name >> base_salary >> sold_nm >> price;
				employees::SalesManager* m = new employees::SalesManager(name, base_salary, sold_nm, price);
				arr.add(m);

			}
			else {
				std::cout << "Choose the correct type\n";
			}
		}
		else if (command == "list") {
			std::cout << arr << std::endl;
		}
		else if (command == "exit") {
			return 0;
		}
		else {
			std::cout << "Unknown command, try again\n";
		}
	}
}