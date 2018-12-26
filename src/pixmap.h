#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct PixMapImage PixMapImage;

typedef int32_t i32;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

void pixmap_image_new            (PixMapImage **image, u32 width, u32 height);
void pixmap_image_free           (PixMapImage  *image);

void pixmap_image_open           (PixMapImage **image, char const *file_path);

u32  pixmap_image_width          (PixMapImage  *image);
u32  pixmap_image_height         (PixMapImage  *image);
u32  pixmap_image_max_color_value(PixMapImage  *image);
