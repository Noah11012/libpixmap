#include "pixmap_draw.h"

int pixmap_draw_line(PixMapImage *image, RGB *rgb, int x1, int y1, int x2, int y2)
{
    int x = x1;
    int y = y1;

    int status = 0;

    for(; x < x2, y < y2; x += 1, y += 1)
    {
        pixmap_image_set_pixel_by_rgb(image, x, y, rgb, &status);

        if(status)
            return -1;
    }

    return 0;
}