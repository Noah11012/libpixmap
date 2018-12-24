#include "pixmap.h"

struct PixMapImage
{
    FILE *image_file;
    u8   *pixels;
    u32   width;
    u32   height;
    u32   maximum_color_value;
};

// parses a number from a file and value is "returned" from *output
// returns 0 if file can still be processed and -1 when EOF is reached

static u32 pixmap_image_read_number(FILE *file, u32 *output);

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

    // PPM images allow for comments virtually ANYWHERE in the file
    // We have to keep this in mind

    u32 image_width = 0;
    u32 image_height = 0;
    u32 image_maximum_color_value = 0;
    u32 number = 0;

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

    if(!(new_image->pixels = malloc(sizeof(u8) * (image_width * number * 3))))
    {
        fclose(file);
        *image = 0;
        return;
    }

    new_image->width = image_width;
    new_image->height = image_height;
   
    // pixels
    
    u32 color = 0;
    u32 pixel_array_index = 0;
    while(pixmap_image_read_number(file, &color) != -1)
        new_image->pixels[pixel_array_index++] = color;

    *image = new_image;

    // TODO(noah): parsing pixels works, but "parses" two zeros seemingly out of nowhere in the beginning
}

u32 pixmap_image_width(PixMapImage *image)
{
    return image->width;
}

u32 pixmap_image_height(PixMapImage *image)
{
    return image->height;
}

static u32 pixmap_image_read_number(FILE *file, u32 *output)
{
    int is_comment = 0;
    int c = 0;
    int number = 0;
    while((c = fgetc(file)) && (!feof(file)))
    {
        if(c == '#')
            is_comment = 1;
        else if(c == '\n')
            is_comment = 0;
        else if(is_comment)
            continue;

        if(isdigit(c))
        {
            number *= 10;
            number += (c - '0');
        }

        if(isspace(c))
        {
            *output = number;
            return 0;
        }
    }

    return -1;
}
