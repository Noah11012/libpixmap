#include "pixmap.h"

struct PixMapImage
{
    FILE *image_file;
    u8   *pixels;
    u32   width;
    u32   height;
    u32   maximum_color_value;
};

// parses a number from a file and *output is filled with the result
// returns 0 if file can still be processed and -1 when EOF is reached
// or an error has occurred. 

static i32 pixmap_image_read_number(FILE *file, u32 *output);

static void pixmap_image_copy_u8(u8 *destination, u8 const *source, int count);

void pixmap_image_new(PixMapImage **image, u32 width, u32 height)
{
    PixMapImage *new_image = 0;
    if(!(new_image = malloc(sizeof(PixMapImage))))
    {
        *image = 0;
        return;
    }

    new_image->width = width;
    new_image->height = height;
    
    if(!(new_image->pixels = malloc(sizeof(u8) * (new_image->width * new_image->height * 3))))
    {
        free(new_image);
        *image = 0;
        return;
    }

    new_image->image_file = 0;
    *image = new_image;
}

void pixmap_image_free(PixMapImage *image)
{
    fclose(image->image_file);
    free(image->pixels);
    free(image);
}

void pixmap_image_open(PixMapImage **image, char const *file_path)
{
    if(!file_path)
    {
        *image = 0;
        return;
    }

    FILE *file = 0;
    if(!(file = fopen(file_path, "r")))
    {
        *image = 0;
        return;
    }

    // The first two bytes in the file MUST be P3
    // Later, we will support P6
    
    u8 signature[2] = { 0 };
    fread(signature, sizeof(u8), 2, file);
    if(!(signature[0] == 'P' && signature[1] == '3'))
    {
        fclose(file);
        *image = 0;
        return;
    }

    // skip over newline character after P3

    fseek(file, 1, SEEK_CUR);

    // PPM images allow for comments virtually ANYWHERE in the file
    // We have to keep this in mind

    u32 image_width = 0;
    u32 image_height = 0;
    u32 image_maximum_color_value = 0;

    // Extract width, height and the maximum color value first
    
    // width
    
    if(pixmap_image_read_number(file, &image_width) == -1)
    {
        fclose(file);
        *image = 0;
        return;
    }

    // height
    
    if(pixmap_image_read_number(file, &image_height) == -1)
    {
        fclose(file);
        *image = 0;
        return;
    }

    // maximum color value
    
    if(pixmap_image_read_number(file, &image_maximum_color_value) == -1)
    {
        fclose(file);
        *image = 0;
        return;
    }

    PixMapImage *new_image = 0;
    if(!(new_image = malloc(sizeof(PixMapImage))))
    {
        fclose(file);
        *image = 0;
        return;
    }

    if(!(new_image->pixels = malloc((sizeof(u8) * 30 * 20 * 3))))
    {
        fclose(file);
        free(new_image);
        *image = 0;
        return;
    }

    new_image->width = image_width;
    new_image->height = image_height;
    
    // pixels
    
    u32 color = 0;
    u32 pixel_array_index = 0;
    while((pixmap_image_read_number(file, &color) != -1))
            new_image->pixels[pixel_array_index++] = color;

    *image = new_image;
}

u32 pixmap_image_get_width(PixMapImage *image)
{
    return image->width;
}

u32 pixmap_image_get_height(PixMapImage *image)
{
    return image->height;
}

u32 pixmap_image_max_color_value(PixMapImage *image)
{
    return image->maximum_color_value;
}

int pixmap_image_set_all_pixels(PixMapImage *image, u8 *new_pixels, int new_pixels_count)
{
    if((image->width * image->height) < new_pixels_count)
        return -1;

    pixmap_image_copy_u8(image->pixels, new_pixels, new_pixels_count * 3);
    return 0;
}

u8 *pixmap_image_get_all_pixels(PixMapImage *image)
{
    return image->pixels;
}

static i32 pixmap_image_read_number(FILE *file, u32 *output)
{
    i32 c = 0;
    // pixmap images can have comments. if the symbol `#` is encountered, fast foward until
    // it reaches a newline and resets the flag.
    u32 is_comment = 0;
    u32 number = 0;
    while((c = fgetc(file)) != EOF)
    {
        if(ferror(file))
            return -1;
        
        if(c == '#')
            is_comment = 1;

        if(is_comment)
            continue;

        if(isspace(c) && !is_comment)
        {
            *output = number;
            return 0;
        }

        number *= 10;
        number += c - '0';
    }

    return -1;
}

static void pixmap_image_copy_u8(u8 *destination, u8 const *source, int count)
{
    int i = 0;
    while(i < count)
    {
        destination[i] = source[i];
        i++;
    }
}

int pixmap_image_set_pixel(PixMapImage *image, u32 x, u32 y, PixMapRGB const *color)
{
    if(!color)
        return -1;
    if((x < 0) || (x > image->width - 1))
        return -1;
    if((y < 0) || (y > image->height - 1))
        return -1;

    *(image->pixels + (x + (y * image->width)) * 3) = color->red;
    *((image->pixels + (x + (y * image->width)) * 3) + 1) = color->green;
    *((image->pixels + (x + (y * image->width)) * 3) + 2) = color->blue;

    return 0;
}

int pixmap_image_get_pixel(PixMapImage *image, u32 x, u32 y, PixMapRGB *color) 
{
    if(!color)
        return -1;
    if((x < 0) || (x > image->width - 1))
        return -1;
    if((y < 0) || (y > image->height - 1))
        return -1;

    u8 *first_color_component = image->pixels + (x + (y * image->width)) * 3;
    color->red = *first_color_component;
    color->green = *(first_color_component + 1);
    color->blue = *(first_color_component + 2);

    return 0;
}

