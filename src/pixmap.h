#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct PixMapImage PixMapImage;
typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} PixMapRGB;

typedef int32_t i32;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

void pixmap_image_new            (PixMapImage **image, char const *name, u32 width, u32 height);
void pixmap_image_free           (PixMapImage  *image);

void pixmap_image_open           (PixMapImage **image, char const *file_path);
int  pixmap_image_save           (PixMapImage  *image);

u32  pixmap_image_get_width      (PixMapImage  *image);
u32  pixmap_image_get_height     (PixMapImage  *image);

int  pixmap_image_set_all_pixels (PixMapImage  *image, u8 *new_pixels, int new_pixels_count);
u8  *pixmap_image_get_all_pixels (PixMapImage  *image);

int  pixmap_image_set_pixel      (PixMapImage  *image, u32 x, u32 y, PixMapRGB const *color);
int  pixmap_image_get_pixel      (PixMapImage  *image, u32 x, u32 y, PixMapRGB *color);
