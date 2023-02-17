
CFLAGS ?= -std=c++17 -Wall -Wextra -Werror -I include/ -g -fno-stack-protector -fsanitize=address

lab-06_int-vector: obj/main.o obj/my_vector.o obj 
	g++ $(CFLAGS) obj/main.o obj/my_vector.o -o lab-06_int-vector
obj/main.o: src/main.cpp include/my_vector.hpp | obj
	g++ $(CFLAGS) -c src/main.cpp -o obj/main.o 
obj/my_vector.o: src/my_vector.cpp include/my_vector.hpp | obj
	g++ $(CFLAGS) -c src/my_vector.cpp -o obj/my_vector.o 
obj:
	mkdir obj
.PHONY: clean
clean:
	rm -rf obj
