
CFLAGS ?= -Wall -Wextra -Werror -I include/ -g -fno-stack-protector

lab-05_c-io: obj/main.o obj/clist.o obj/point_list.o obj 
	gcc $(CFLAGS) obj/main.o obj/clist.o obj/point_list.o -o lab-05_c-io
obj/main.o: src/main.c include/clist.h include/point_list.h | obj
	gcc $(CFLAGS) -c src/main.c -o obj/main.o 
obj/clist.o: src/clist.c | obj
	gcc $(CFLAGS) -c src/clist.c -o obj/clist.o 
obj/point_list.o: src/point_list.c include/point_list.h | obj
	gcc $(CFLAGS) -c src/point_list.c -o obj/point_list.o
obj:
	mkdir obj
.PHONY: clean
clean:
	rm -rf obj
