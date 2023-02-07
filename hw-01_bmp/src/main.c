#include "bmp.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	bmp_t bmp;
	bmp_t bmp_crop_rotate;
	if (argc >= 8) {
		if (strcmp(argv[1], "crop-rotate") == 0) {
			char* in_bmp = argv[2];
			char* out_bmp = argv[3];
			int x = atoi(argv[4]);
			int y = atoi(argv[5]);
			int w = atoi(argv[6]);
			int h = atoi(argv[7]);
			load_bmp(in_bmp, &bmp);
			int bmp_w = bmp.infoheader.biWidth;
			int bmp_h = bmp.infoheader.biHeight;
			if (x + h > bmp_h || y + w > bmp_w || x + h <= x || y + w <= y || x < 0 || y < 0) {
				return 1;
			}
			bmp_crop_rotate = crop_rotate(&bmp, x, y, w, h);
			save_bmp(out_bmp, &bmp_crop_rotate);
			free_bmp(&bmp);
			free_bmp(&bmp_crop_rotate);
		}
		else {
			return 1;
		}
	}
	else {
		return 1;
	}

}