#ifndef __HEAD_H_
#define __HEAD_H_

#include <stdio.h>
#include <linux/fb.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include "sqlite3.h"

#define RED   2
#define GREEN 1
#define BLUE  0

struct coordinate 
{
	int x;
	int y;
	int press;
};

struct phone_info
{
	char name[20];
	char telephone[20];
	char photo[20];
	char music[20];
};

struct image_info
{
	int height;
	int width;
	int bpp;
};

struct header
{
	int16_t type;
	int32_t size;
	int16_t reserved1;
	int16_t reserved2;
	int32_t offbits;
}__attribute__((packed));

struct info
{
	int32_t size;
	int32_t width;
	int32_t height;
	int16_t planes;

	int16_t bit_count;
	int32_t compression;
	int32_t size_img;
	int32_t X_pel;
	int32_t Y_pel;
	int32_t clrused;
	int32_t clrImportant;
}__attribute__((packed));       

char *init_lcd(struct fb_var_screeninfo *pvinfo);

char *load_bmp(char *bmpfile, struct image_info *pimgfo);

void display_bmp(char *fbmemy, struct fb_var_screeninfo *pvinfo, char *imgdata,
		struct image_info *pimgfo, int xoffset, int yoffset);

#endif