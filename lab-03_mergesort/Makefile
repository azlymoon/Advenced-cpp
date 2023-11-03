
CFLAGS ?= -Wall -Wextra -Werror -I include/ -g -fno-stack-protector

lab-03_mergesort: obj/mergesort.o obj/main.o obj
	gcc $(CFLAGS) obj/mergesort.o obj/main.o -o lab-03_mergesort 
obj/main.o: src/main.c include/mergesort.h | obj
	gcc $(CFLAGS) -c src/main.c -o obj/main.o 
obj/mergesort.o: src/mergesort.c include/mergesort.h | obj
	gcc $(CFLAGS) -c src/mergesort.c -o obj/mergesort.o 
obj:
	mkdir obj
.PHONY: clean
clean:
	rm -rd obj


