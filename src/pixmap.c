#include "pixmap.h"

struct PixMapImage
{
    FILE *image_file;
    u8   *pixels;
    int   width;
    int   height;
};

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

    FILE *image_file = 0;
    if(!(image_file = fopen(file_path, "r")))
    {
        *image = 0;
        return;
    }

    // The first two bytes in the file MUST be P3
    // Later, we will support P6
    
    u8 signature[2] = { 0 };
    fread(signature, sizeof(u8), 2, image_file);
    if(!(signature[0] == 'P' && signature[1] == '3'))
    {
        *image = 0;
        return;
    }

    // PPM images allow for comments virtually ANYWHERE in the file
    // We have to keep this in mind

    int is_comment = 0;
    int image_width = 0;
    int image_height = 0;
    int c = 0;

    // Extract width and height first
    
    // width
    
    while((c = fgetc(image_file)) && (!feof(image_file)))
    {
        if(c == '#')
            is_comment = 1;    
        else if(c == '\n')
            is_comment = 0;
        else if(is_comment)
            continue;

        if(isdigit(c))
        {
            image_width *= 10;
            image_width += c - '0';
        }

        if(isspace(c))
            break;
    }

    // height
    
    while((c = fgetc(image_file)) && (!feof(image_file)))
    {
        if(c == '#')
            is_comment = 1;    
        else if(c == '\n')
            is_comment = 0;
        else if(is_comment)
            continue;

        if(isdigit(c))
        {
            image_height *= 10;
            image_height += c - '0';
        }

        if(isspace(c))
            break;
    }

    PixMapImage *new_image = 0;
    pixmap_image_new(&new_image, image_width, image_height);
    if(!new_image)
    {
        *image = 0;
        return;
    }

    if(!(new_image->pixels = malloc(sizeof(u8) * (image_width * image_height * 3))))
    {
        *image = 0;
        return;
    }

    new_image->width = image_width;
    new_image->height = image_height;

    // TODO(noah): Parse pixels
}
