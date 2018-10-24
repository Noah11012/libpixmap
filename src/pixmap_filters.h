#pragma once

#include "pixmap.h"

typedef struct _PixMapComponents {
    PixMapImage *red;
    PixMapImage *green;
    PixMapImage *blue;
} PixMapComponents;

void pixmap_filter_brightness(PixMapImage *image, int brighness, int *error);
PixMapComponents *pixmap_filter_split_into_components(PixMapImage *image);
void pixmap_filter_close_components(PixMapComponents *components);
void pixmap_filter_desaturate_lightness(PixMapImage *image, int *error);
void pixmap_filter_desaturate_average(PixMapImage *image, int *error);
