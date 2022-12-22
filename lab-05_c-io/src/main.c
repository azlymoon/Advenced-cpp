#include "point_list.h"
#include "clist.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
	struct intrusive_list l;
	init_list(&l);

	if (strcmp(argv[1], "loadtext") == 0) {
		char* path_in_file = argv[2];
		read_txt_file(&l, path_in_file);
	}
	else if (strcmp(argv[1], "loadbin") == 0) {
		char* path_in_file = argv[2];
		read_bin_file(&l, path_in_file);
	}

	for (int i = 3; i < argc; i++) {
		if (strcmp(argv[i], "savetext") == 0) {
			i += 1;
			char* path_out_file = argv[i];
			write_all_points_txt_file(&l, path_out_file);
		}
		else if (strcmp(argv[i], "savebin") == 0) {
			i += 1;
			char* path_out_file = argv[i];
			write_all_points_bin_file(&l, path_out_file);
		}
		else if (strcmp(argv[i], "print") == 0) {
			i += 1;
			char* format = argv[i];
			apply(&l, print, format);
			printf("\n");
		}
		else if (strcmp(argv[i], "count") == 0) {
			int size_list = 0;
			apply(&l, count, &size_list);
			printf("%d\n", size_list);
		}
	}

	remove_all_points(&l);

	return 0;
}