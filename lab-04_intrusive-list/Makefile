
CFLAGS ?= -Wall -Wextra -Werror -I include/ -g -fno-stack-protector

lab-04_intrusive-list: obj/main.o obj/clist.o obj
	gcc $(CFLAGS) obj/main.o obj/clist.o -o lab-04_intrusive-list 
obj/main.o: src/main.c include/clist.h | obj
	gcc $(CFLAGS) -c src/main.c -o obj/main.o 
obj/clist.o: src/clist.c | obj
	gcc $(CFLAGS) -c src/clist.c -o obj/clist.o 
obj:
	mkdir obj
.PHONY: clean
clean:
	rm -rf obj
