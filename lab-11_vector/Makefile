
CFLAGS ?= -std=c++17 -Wall -Wextra -Werror -I include/ -g -fno-stack-protector

lab-11_vector: obj/main.o obj/my_vector_impl.o obj
	g++ $(CFLAGS) obj/main.o obj/my_vector_impl.o -o lab-11_vector
obj/main.o: src/main.cpp include/my_vector.hpp | obj
	g++ $(CFLAGS) -c src/main.cpp -o obj/main.o 
obj/my_vector_impl.o: include/my_vector_impl.hpp include/my_vector.hpp | obj
	g++ $(CFLAGS) -c include/my_vector_impl.hpp -o obj/my_vector_impl.o
obj:
	mkdir obj
.PHONY: clean
clean:
	rm -rf obj
