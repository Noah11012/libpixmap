#include "pixmap.h"

struct _PixMapImage
{
    FILE *_image_file;
    int _width;
    int _height;
    RGB *_pixels;
    int _max_color_value;
};

PixMapImage *pixmap_image_new(char const *name, int width, int height, int max_color_val)
{
    PixMapImage *new_image = malloc(sizeof(*new_image));

    if(!new_image) return 0;

    new_image->_width = width;
    new_image->_height = height;
    new_image->_max_color_value = max_color_val <= 255 ? max_color_val : 255;

    new_image->_pixels = malloc(sizeof(RGB) * (new_image->_width * new_image->_height));

    if(!new_image->_pixels)
    {
        free(new_image);
        return 0;
    }

    new_image->_image_file = fopen(name, "w");

    if(!new_image->_image_file)
    {
        free(new_image->_pixels);
        free(new_image);
        return 0;
    }

    return new_image;
}

PixMapImage *pixmap_image_open(char const *name)
{
    PixMapImage *new_image = malloc(sizeof(*new_image));

    if(!new_image) return 0;

    new_image->_pixels = malloc(sizeof(RGB) * (new_image->_width * new_image->_height));
    
    if(!new_image->_pixels)
    {
        free(new_image);
        return 0;
    }

    new_image->_image_file = fopen(name, "r+");

    if(!new_image->_image_file)
    {
        free(new_image->_pixels);
        free(new_image);
        return 0;
    }

    unsigned char sig[3];
    fread(sig, sizeof(unsigned char), 2, new_image->_image_file);

    if(!(sig[0] == 'P' && sig[1] == '3')) return 0;

    int c;
    int comment = 0;
    while((c = fgetc(new_image->_image_file)) != EOF)
    {
        if(c == '#') comment = 1;
        if(c == '\n') comment = 0;

        if(isdigit(c) && !comment)
        {
            ungetc(c, new_image->_image_file);
            fscanf(new_image->_image_file, "%d %d\n%d", &new_image->_width, &new_image->_height,
                                                        &new_image->_max_color_value);
            break;
        }
    }

    // TODO: parse pixels into array

    return new_image;
}

void pixmap_image_set_pixel(PixMapImage *image, unsigned int x, unsigned int y, unsigned int red, unsigned int green, unsigned int blue)
{
    if(x > image->_width || y > image->_height) return;

    red = red <= 255 ? red : 255;
    green = green <= 255 ? green : 255;
    blue = blue <= 255 ? blue : 255;

    RGB color = { red, green, blue };

    image->_pixels[x + (y * image->_width)] = color;
}

RGB *pixmap_image_get_pixel(PixMapImage *image, unsigned int x, unsigned int y)
{
    if(x > (image->_width - 1) || y > (image->_height - 1)) return 0;

    return &image->_pixels[x + (y * image->_width)];
}

void pixmap_image_save(PixMapImage *image)
{
    fprintf(image->_image_file, "%s\n%d %d\n%d\n", "P3", image->_width, image->_height, image->_max_color_value);
    
    int i = 0;
    int w = 0;
    while(i < image->_width * image->_height)
    {        
        if(w > 2)
        {
            fprintf(image->_image_file, "%d %d %d\n",
                    image->_pixels[i].red, image->_pixels[i].green, image->_pixels[i].blue);
            w = 0;
        } else {
            fprintf(image->_image_file, "%d %d %d ",
                    image->_pixels[i].red, image->_pixels[i].green, image->_pixels[i].blue);
            
        }
 
        w++;
        i++;
    }
}

int pixmap_image_get_width(PixMapImage *image)
{
    return image->_width;
}

int pixmap_image_get_height(PixMapImage *image)
{
    return image->_height;
}

int pixmap_image_get_max_color_value(PixMapImage *image)
{
    return image->_max_color_value;
}

void pixmap_image_close(PixMapImage *image)
{
    if(!image) return;

    fclose(image->_image_file);
    free(image->_pixels);
    free(image);
}
