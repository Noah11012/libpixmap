#include "pixmap_filters.h"

void pixmap_filter_brightness(PixMapImage *image, int brighness)
{
    int total_x = pixmap_image_get_width(image);
    int total_y = pixmap_image_get_height(image);
    int max_value = pixmap_image_get_max_color_value(image);

    for(int x = 0; x < total_x; x++)
    {
	for(int y = 0; y < total_y; y++)
	{
	    RGB pixel = pixmap_image_get_pixel(image, x, y);
	    pixel.red += brightness;
	    pixel.green += brightness;
	    pixel.blue += brightness;

	    /* Clamp pixel values to max value or zero */
	    pixel.red = pixel.red > max_value ? max_value :
		pixel.red < 0 ? 0 : pixel.red;

	    pixel.green = pixel.green > max_value ? max_value :
		pixel.green < 0 ? 0 : pixel.green;

	    pixel.blue = pixel.blue > max_value ? max_value :
		pixel.blue < 0 ? 0 : pixel.blue;
	}
    }
}
