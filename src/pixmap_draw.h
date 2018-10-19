#pragma once

#include <math.h>
#include "pixmap.h"


int pixmap_image_draw_line(PixMapImage *image, RGB *rgb, int x1, int y1, int x2, int y2);
int pixmap_image_draw_rectangle_by_points(PixMapImage *image, RGB *rgb,
					                      int x1, int y1, int x2, int y2);
int pixmap_image_draw_rectangle_by_size(PixMapImage *image, RGB *rgb,
					                    int x, int y, int dx, int dy);

