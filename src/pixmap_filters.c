#include "pixmap_filters.h"

void pixmap_filter_brightness(PixMapImage *image, int brightness, int *error)
{
    int total_x = pixmap_image_get_width(image);
    int total_y = pixmap_image_get_height(image);
    int max_value = pixmap_image_get_max_color_value(image);

    for(int y = 0; y < total_y; y++)
    {
	for(int x = 0; x < total_x; x++)
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

	    pixmap_image_set_pixel_by_rgb(image, x, y, &pixel, error);
	}
    }
}

PixMapComponents *pixmap_filter_split_into_components(PixMapImage *image)
{
    int width = pixmap_image_get_width(image);
    int height = pixmap_image_get_height(image);
    int max_value = pixmap_image_get_max_color_value(image);
    PixMapImageType type = pixmap_image_get_type(image);
    
    PixMapComponents *res = malloc(sizeof(PixMapComponents));

    if(!res)
	return NULL;

    res->red = pixmap_image_new(NULL, width, height, max_value, type);
    res->green = pixmap_image_new(NULL, width, height, max_value, type);
    res->blue = pixmap_image_new(NULL, width, height, max_value, type);

    if(!res->red || !res->green || !res->blue)
      return NULL

    int *error = malloc(sizeof(int));
    *error = 0;
    for(int y = 0; y < height; y++)
    {
	for(int x = 0; x < width; x++)
	{
	    RGB pixel = pixmap_image_get_pixel(image, x, y);
	    pixmap_image_set_pixel(res->red, x, y, pixel.red, 0, 0, error);
	    pixmap_image_set_pixel(res->green, x, y, 0, pixel.green, 0, error);
	    pixmap_image_set_pixel(res->blue, x, y, 0, 0, pixel.blue, error);

	    if(*error)
	    {
		pixmap_image_close(res->red);
		pixmap_image_close(res->green);
		pixmap_image_close(res->blue);
		return NULL;
	    }
	}
    }
    free(error);
    return res;
}

void pixmap_filter_close_components(PixMapComponents *components)
{
    pixmap_image_close(components->red);
    pixmap_image_close(components->green);
    pixmap_image_close(components->blue);

    free(components);
}
