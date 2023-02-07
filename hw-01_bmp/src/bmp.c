#include "bmp.h"
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>

void load_bmp(char* in_bmp, bmp_t* bmp) {
	FILE* in;
	if ((in = fopen(in_bmp, "rb")) == NULL)
		exit(1);
	fseek(in, 0, SEEK_SET);
	fread(&bmp->fileheader, sizeof(bmp_fileheader_t), 1, in);
	fread(&bmp->infoheader, sizeof(bmp_infoheader_t), 1, in);

	int32_t w = bmp->infoheader.biWidth;
	int32_t h = bmp->infoheader.biHeight;
	int whitespace = (4 - bmp->infoheader.biWidth * 3 % 4) % 4;

	fseek(in, bmp->fileheader.bfOffBits, SEEK_SET);
	void* data = malloc(sizeof(pixel_t) * w * h);
	assert(data);
	bmp->rect.data = (pixel_t*)data;
	bmp->rect.pixels = (pixel_t**)malloc(sizeof(pixel_t*) * h);
	assert(bmp->rect.pixels);
	for (int32_t i = 0; i < h; i++) {
		bmp->rect.pixels[i] = data;
		fread(data, sizeof(pixel_t), w, in);
		fseek(in, whitespace, SEEK_CUR);
		data += sizeof(pixel_t) * w;
		if (ferror(in)) {
			exit(1);
		}
	}
	fclose(in);
}

rectangle_t crop(bmp_t* bmp, int32_t x, int32_t y, int32_t w, int32_t h){
	pixel_t* data = (pixel_t*)malloc(sizeof(pixel_t) * w * h);
	assert(data);
	pixel_t** pixels = (pixel_t**)malloc(sizeof(pixel_t*) * h);
	assert(pixels);
	rectangle_t rect_new;
	rect_new.data = data;
	rect_new.pixels = pixels;
	for (int32_t i = 0; i < h; i++) {
		pixels[i] = data;
		for (int32_t j = 0; j < w; j++) {
			*data = bmp->rect.pixels[bmp->infoheader.biHeight - h - y + i][x + j];
			data++;
		}
	}
	return rect_new;
}
rectangle_t rotate(rectangle_t rect, int32_t w, int32_t h) {
	int32_t w_new = h, h_new = w;
	pixel_t* data = (pixel_t*)malloc(sizeof(pixel_t) * w_new * h_new);
	assert(data);
	pixel_t** pixels = (pixel_t**)malloc(sizeof(pixel_t*) * h_new);
	assert(pixels);
	rectangle_t rect_new;
	rect_new.data = data;
	rect_new.pixels = pixels;
	for (int32_t i = 0; i < h_new; i++) {
		pixels[i] = data;
		for (int32_t j = 0; j < w_new; j++) {
			*data = rect.pixels[j][w - i - 1];
			data++;
		}
	}
	free(rect.data);
	free(rect.pixels);
	return rect_new;
}

void save_bmp(char* out_bmp, bmp_t* bmp) {
	FILE* out = fopen(out_bmp, "wb");
	fseek(out, 0, SEEK_SET);
	fwrite(&bmp->fileheader, sizeof(bmp_fileheader_t), 1, out);
	fwrite(&bmp->infoheader, sizeof(bmp_infoheader_t), 1, out);


	int32_t w = bmp->infoheader.biWidth;
	int32_t h = bmp->infoheader.biHeight;
	int whitespace = (4 - bmp->infoheader.biWidth * 3 % 4) % 4;
	unsigned char null = 0;

	fseek(out, bmp->fileheader.bfOffBits, SEEK_SET);
	for (int i = 0; i < h; i++) {
		fwrite(bmp->rect.pixels[i], sizeof(pixel_t), w, out);
		for (int j = 0; j < whitespace; j++) {
			fwrite(&null, sizeof(unsigned char), 1, out);
		}
	}
}

bmp_t crop_rotate(bmp_t* bmp, int32_t x, int32_t y, int32_t w, int32_t h) {
	rectangle_t rect = crop(bmp, x, y, w, h);
	rect = rotate(rect, w, h);
	bmp_t bmp_new;
	bmp_new.fileheader = bmp->fileheader;
	bmp_new.infoheader = bmp->infoheader;
	bmp_new.infoheader.biWidth = h;
	bmp_new.infoheader.biHeight = w;
	int whitespace = (4 - bmp_new.infoheader.biWidth * 3 % 4) % 4;
	bmp_new.fileheader.bfSize = bmp->fileheader.bfOffBits + w * h * 3 + whitespace * bmp_new.infoheader.biHeight;
	bmp_new.infoheader.biSizeImage = w * h * 3 + whitespace * bmp_new.infoheader.biHeight;

	bmp_new.rect = rect;
	return bmp_new;
}

void free_bmp(bmp_t* bmp) {
	free(bmp->rect.data);
	free(bmp->rect.pixels);
}