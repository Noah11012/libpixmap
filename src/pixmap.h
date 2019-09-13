#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

typedef int32_t i32;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

struct
{
    char const *file_path;
    u8         *pixels;
    u32         width;
    u32         height;
    u32         maximum_color;
} typedef PixMapImage;

struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} typedef PixMapRGB;

void pixmap_image_new            (PixMapImage **image, char const *name, u32 width, u32 height);
void pixmap_image_free           (PixMapImage  *image);

void pixmap_image_open           (PixMapImage **image, char const *file_path);
int  pixmap_image_save           (PixMapImage  *image);

int  pixmap_image_set_pixel      (PixMapImage  *image, u32 x, u32 y, PixMapRGB const *color);
int  pixmap_image_get_pixel      (PixMapImage  *image, u32 x, u32 y, PixMapRGB *color);
