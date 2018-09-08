#include "ppm.h"

struct _PixMapImage
{
    FILE *_image_file;
    int _width;
    int _height;
    unsigned char *_pixels;
    int _max_color_value;
};

PixMapImage *pixmap_image_new(char const *name, int width, int height, int max_color_val)
{
    PixMapImage *new_image = malloc(sizeof(*new_image));

    if(!new_image) return 0;

    new_image->_width = width;
    new_image->_height = height;
    new_image->_max_color_value = max_color_val <= 255 ? max_color_val : 255;

    new_image->_pixels = malloc(sizeof(unsigned char) * (width * height));

    if(!new_image->_pixels) return 0;

    new_image->_image_file = fopen(name, "r+");

    if(!new_image->_image_file) return 0;

    return new_image;
}

int pixmap_image_get_width(PixMapImage *image)
{
    return !image ? image->_width : -1;
}

int pixmap_image_get_height(PixMapImage *image)
{
    return !image ? image->_height : -1;
}

void pixmap_image_close(PixMapImage *image)
{
    if(!image) return;

    fclose(image->_image_file);
    free(image->_pixels);
    free(image);
}
