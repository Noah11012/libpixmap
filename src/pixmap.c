#include "pixmap.h"

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

    new_image->_pixels = malloc(sizeof(unsigned char) * (width * height * 3));

    if(!new_image->_pixels) return 0;

    new_image->_image_file = fopen(name, "r+");

    if(!new_image->_image_file) return 0;

    return new_image;
}

void pixmap_image_set_pixel(PixMapImage *image, unsigned int x, unsigned int y, unsigned int red, unsigned int green, unsigned int blue)
{
    if(x > image->_width || y > image->_height) return;

    red = red <= 255 ? red : 255;
    green = green <= 255 ? green : 255;
    blue = blue <= 255 ? blue : 255;

    image->_pixels[x + (y * image->_width) * 3] = red;
    image->_pixels[x + (y * image->_width * 3) + 1] = green;
    image->_pixels[x + (y * image->_width * 3) + 2] = blue;
}

void pixmap_image_save(PixMapImage *image)
{
    fprintf(image->_image_file, "%s\n%d %d\n%d", "P3", image->_width, image->_height, image->_max_color_value);
    
    int i = 0;
    int w = 0;
    while(i < image->_width * image->_height * 3)
    {

        fprintf(image->_image_file, " %d %d %d",
                image->_pixels[i], image->_pixels[i + 1], image->_pixels[i + 2]);
        
        if(w == image->_width)
        {
            fprintf(image->_image_file, "\n");
            w = 0;
        }
        
        i++;
        w++;
    }
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
