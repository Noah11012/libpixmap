#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct _PixMapImage PixMapImage;


PixMapImage *pixmap_image_new       (char const *name, int width, int height, int max_color_val);
int          pixmap_image_get_width (PixMapImage *image);
int          pixmap_image_get_height(PixMapImage *image);
void         pixmap_image_close     (PixMapImage *image);