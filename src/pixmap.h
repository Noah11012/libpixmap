#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct _PixMapImage PixMapImage;

typedef struct _RGB
{
    int red;
    int green;
    int blue;
} RGB;

typedef enum
{
    Text = 1,
    Binary = 2
} PixMapImageType;

PixMapImage *pixmap_image_new                (char const *name, int width, int height, int max_color_val, PixMapImageType type);
PixMapImage *pixmap_image_open               (char const *name);
PixMapImage *pixmap_image_copy               (PixMapImage *image, char const *new_name, PixMapImageType type);
RGB         *pixmap_image_get_pixel_array    (PixMapImage *image);
void         pixmap_image_set_pixel          (PixMapImage *image,
                                              int x, int y,
                                              int red, int green, int blue,
                                              int *error);
void         pixmap_image_set_pixel_by_rgb   (PixMapImage *image,
                                              int x, int y,
                                              RGB *rgb, int *error);
RGB          pixmap_image_get_pixel          (PixMapImage *image, int x, int y);
int          pixmap_image_save               (PixMapImage *image);
int          pixmap_image_get_width          (PixMapImage *image);
int          pixmap_image_get_height         (PixMapImage *image);
int          pixmap_image_get_max_color_value(PixMapImage *image);
void         pixmap_image_foreach_pixel      (PixMapImage *image,
					      void (*func)(RGB pixel, void *func_arg),
					      void * arg);
void         pixmap_image_close              (PixMapImage *image);
