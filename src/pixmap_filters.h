#pragma once

#include "pixmap.h"

typedef struct _PixMapComponents {
    PixMapImage *red;
    PixMapImage *green;
    PixMapImage *blue;
} PixMapComponents;

void pixmap_filter_brightness(PixMapImage *image, int brighness, int *error);
PixMapComponents *pixmap_filter_split_into_components(PixMapImage *image);
