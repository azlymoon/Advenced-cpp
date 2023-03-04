#pragma once

#include <stdint.h>
#include <stdio.h>

#pragma pack(push, 1)

typedef struct {
	uint16_t bfType;
	uint32_t bfSize;
	uint16_t bfReserved1;
	uint16_t bfReserved2;
	uint32_t bfOffBits;
} bmp_fileheader_t;

typedef struct {
	uint32_t biSize;
	int32_t biWidth;
	int32_t biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	int32_t biXPelsPerMeter;
	int32_t biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
} bmp_infoheader_t;

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} pixel_t;

#pragma pack(pop)

typedef struct {
	pixel_t* data;
	pixel_t** pixels;
}rectangle_t;

typedef struct {
	bmp_fileheader_t fileheader;
	bmp_infoheader_t infoheader;
	rectangle_t rect;
} bmp_t;

void load_bmp(char* in_bmp, bmp_t* bmp);
rectangle_t crop(bmp_t* bmp, int32_t x, int32_t y, int32_t w, int32_t h);
rectangle_t rotate(rectangle_t rectp, int32_t w, int32_t h);
void save_bmp(char* out_bmp, bmp_t* bmp);
bmp_t crop_rotate(bmp_t* bmp, int32_t x, int32_t y, int32_t w, int32_t h);
void free_bmp(bmp_t* bmp);