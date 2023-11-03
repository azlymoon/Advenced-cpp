
CFLAGS ?= -Wall -Wextra -Werror -I include/

lab-02_cstrings: obj/test.o obj/test_str.o obj/str.o obj
	gcc $(CFLAGS) obj/test.o obj/test_str.o obj/str.o -o lab-02_cstrings
obj/str.o: src/str.c include/str.h | obj
	gcc $(CFLAGS) -c src/str.c -o obj/str.o
obj/test.o: src/test.c src/test_str.c include/str.h include/test_str.h | obj
	gcc $(CFLAGS) -c src/test.c -o obj/test.o
obj/test_str.o: src/test_str.c include/str.h include/test_str.h | obj
	gcc $(CFLAGS) -c src/test_str.c -o obj/test_str.o
obj:
	mkdir obj
.PHONY: clean
clean:
	rm -rf obj