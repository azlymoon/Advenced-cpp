
CFLAGS ?= -std=c++17 -Wall -Wextra -Werror -I include/ -g -fno-stack-protector

lab-10_cppio: obj/main.o obj/bin_manip.o obj/employees.o obj 
	g++ $(CFLAGS) obj/main.o obj/bin_manip.o obj/employees.o -o lab-10_cppio
obj/main.o: src/main.cpp include/employees.h | obj
	g++ $(CFLAGS) -c src/main.cpp -o obj/main.o 
obj/employees.o: src/employees.cpp include/employees.h | obj
	g++ $(CFLAGS) -c src/employees.cpp -o obj/employees.o 
obj/bin_manip.o: src/bin_manip.cpp include/bin_manip.h | obj
	g++ $(CFLAGS) -c src/bin_manip.cpp -o obj/bin_manip.o 
obj:
	mkdir obj
.PHONY: clean
clean:
	rm -rf obj
