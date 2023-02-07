
CFLAGS ?= -Wall -Wextra -Werror -I include/ -g -fno-stack-protector -fsanitize=address


hw-01_bmp: obj/main.o obj/bmp.o obj
	gcc $(CFLAGS) obj/bmp.o obj/main.o -o hw-01_bmp
obj/main.o: src/main.c include/bmp.h | obj
	gcc $(CFLAGS) -c src/main.c -o obj/main.o 
obj/bmp.o: src/bmp.c include/bmp.h | obj
	gcc $(CFLAGS) -c src/bmp.c -o obj/bmp.o 
obj:
	mkdir obj
.PHONY: clean
clean:
	rm -rd obj


