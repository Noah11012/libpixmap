#include "pixmap_filters.h"

void pixmap_filter_brightness(PixMapImage *image, int brighness)
{
    int x, y;

    for(y = 0; y < pixmap_image_get_height(image); y++)
    {
        for(x = 0; x < pixmap_image_get_width(image); x++)
        {
            RGB color = pixmap_image_get_pixel(image, x, y);
            color.red += brighness;
            color.green += brighness;
            color.blue += brighness;

            color.red = color.red > image->_max_color_value ? color.red : image->_max_color_value;
            color.green = color.green > image->_max_color_value ? color.green : image->_max_color_value;
            color.blue = color.blue > image->_max_color_value ? color.blue : image->_max_color_value;

            pixmap_image_set_pixel_by_rgb(image, x, y, &color, 0);
        }
    }
}
