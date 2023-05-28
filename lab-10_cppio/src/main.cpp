#include <iostream>
#include <sstream>
#include "employees.h"
#include "bin_manip.h"

int main() {
	/*std::string command;
	employees::EmployeesArray arr;
	while (true) {
		std::cin >> command;
		if (command == "load") {

		}
		else if (command == "save") {

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
			std::cout << arr;
		}
		else if (command == "exit") {
			return 0;
		}
		else {
			std::cout << "Unknown command, try again\n";
		}
	}*/

	std::stringstream s;
	int x = 0;
	s << bin_manip::write_int32(x);  // Теперь в s лежит четыре байта: 0A 00 00 00.
	s >> bin_manip::read_int32(x);  // Обратная операция: присваивает x = 10.
	std::cout << x << std::endl;
	s.write("\x12\x34\x56\0", 4);
	s >> bin_manip::read_int32(x);  // x = 0x00563412 = 5649426
	std::cout << x << std::endl;

}