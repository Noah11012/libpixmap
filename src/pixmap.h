#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct _PixMapImage PixMapImage;


PixMapImage *pixmap_image_new                (char const *name, int width, int height, int max_color_val);
PixMapImage *pixmap_image_open               (char const *name);
void         pixmap_image_set_pixel          (PixMapImage *image,
                                              unsigned int x, unsigned int y,
                                              unsigned int red, unsigned int green, unsigned int blue);
void         pixmap_image_save               (PixMapImage *image);
int          pixmap_image_get_width          (PixMapImage *image);
int          pixmap_image_get_height         (PixMapImage *image);
int          pixmap_image_get_max_color_value(PixMapImage *image);
void         pixmap_image_close              (PixMapImage *image);