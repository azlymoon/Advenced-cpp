lab-01_makefile: obj/main.o obj/util.o obj/algorithm.o obj/io.o
	gcc -Wall -Wextra -Werror -I include/ obj/main.o obj/util.o obj/algorithm.o obj/io.o -o lab-01_makefile
obj/main.o: src/main.c include/io.h include/util.h include/algorithm.h | obj
	gcc -Wall -Wextra -Werror -I include/ -c src/main.c -o obj/main.o
obj/util.o: src/util.c include/util.h include/io.h | obj
	gcc -Wall -Wextra -Werror -I include/ -c src/util.c -o obj/util.o
obj/io.o: src/io.c include/io.h | obj
	gcc -Wall -Wextra -Werror -I include/ -c src/io.c -o obj/io.o
obj/algorithm.o: src/algorithm.c include/algorithm.h include/io.h include/util.h | obj
	gcc -Wall -Wextra -Werror -I include/ -c src/algorithm.c -o obj/algorithm.o
obj:
	mkdir obj
.PHONY: clean
clean:
	rm -rf obj