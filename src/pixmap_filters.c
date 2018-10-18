#include "pixmap_filters.h"

void pixmap_filter_brightness(PixMapImage *image, int brighness)
{
    int x, y, i;

    for(y = 0; y < pixmap_image_get_height(image); y++)
    {
        for(x = 0; x < pixmap_image_get_width(image); x++)
        {
            RGB color = pixmap_image_get_pixel(image, x, y);
            color.red + brighness;
            color.green + brighness;
            color.blue + brighness;

            color.red = color.red > 255 ? color.red : 0;
            color.green = color.green > 255 ? color.green : 0;
            color.blue = color.blue > 255 ? color.blue : 0;

            pixmap_image_set_pixel_by_rgb(image, x, y, &color, 0);
        }
    }
}