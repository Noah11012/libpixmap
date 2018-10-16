#include "pixmap.h"

struct _PixMapImage
{
    char *_file_name;
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

    new_image->_file_name = name;

    return new_image;
}

PixMapImage *pixmap_image_open(char const *name)
{
    FILE *image_file = fopen(new_image->_file_name, "r+");
    if(!image_file)
    {
        free(new_image);
        return 0;
    }

    PixMapImage *new_image = malloc(sizeof(*new_image));

    if(!new_image) return 0;

    new_image->_file_name = name;

    unsigned char sig[3];
    fread(sig, sizeof(unsigned char), 2, image_file);

    if(!(sig[0] == 'P' && sig[1] == '3'))
    {
        fclose(image_file);
        free(new_image);
        return 0;
    }

    /* Three while loops to get width, height, and maximum color value */
    /* Looks hacky and probably should be improved later */
    int c;
    int comment = 0;
    new_image->_width = 0;
    new_image->_height = 0;
    while((c = fgetc(image_file)) != EOF)
    {
        if(c == '#') comment = 1;
        if(c == '\n') comment = 0;

        if(isdigit(c) && !comment)
        {
            ungetc(c, image_file);
            fscanf(image_file, "%d", &new_image->_width);
            break;
        }
    }

    while((c = fgetc(image_file)) != EOF)
    {
        if(c == '#') comment = 1;
        if(c == '\n') comment = 0;

        if(isdigit(c) && !comment)
        {
            ungetc(c, image_file);
            fscanf(image_file, "%d", &new_image->_height);
            break;
        }
    }

    while((c = fgetc(image_file)) != EOF)
    {
        if(c == '#') comment = 1;
        if(c == '\n') comment = 0;

        if(isdigit(c) && !comment)
        {
            ungetc(c, image_file);
            fscanf(image_file, "%d", &new_image->_max_color_value);
            break;
        }
    }

    new_image->_width = new_image->_width > 0 ? new_image->_width : 1;
    new_image->_height = new_image->_height > 0 ? new_image->_height : 1;

    new_image->_pixels = malloc(sizeof(RGB) * (new_image->_width * new_image->_height));

        
    if(!new_image->_pixels)
    {
        fclose(image_file);
        free(new_image);
        return 0;
    }

    RGB pixel;
    unsigned int a = 0;
    int b = 1;
    int pos = 0;

    while((c = fgetc(image_file)) != EOF)
    {
        a = 0;
        if(isdigit(c))
        {
            ungetc(c, image_file);
            if(b > 3)
            {
                new_image->_pixels[pos] = pixel;
                pos++;
                b = 1;
            }
            
            while((c = fgetc(image_file)) != EOF && c != ' ')
            {
                a *= 10;
                a += (c - '0');
            }

            printf("COLOR: %u\n", a);

            if(b == 1)
                pixel.red = a;
            else if(b == 2)
                pixel.green = a;
            else if(b == 3)
                pixel.blue = a;
            
            b++;
        }
    }

    fclose(image_file);

    return new_image;
}

PixMapImage *pixmap_image_copy(PixMapImage *image, char const *new_name)
{
    PixMapImage *copy_image = pixmap_image_new(new_name, image->_width, image->_height, image->_max_color_value);
    
    if(!copy_image) return 0;

    int i = 0;
    while(i < copy_image->_width * copy_image->_height)
    {
        copy_image->_pixels[i] = image->_pixels[i];
        i++;
    }

    return copy_image;
}

void pixmap_image_set_pixel(PixMapImage *image, unsigned int x, unsigned int y, unsigned int red, unsigned int green, unsigned int blue, int *error)
{
    if(x > (image->_width - 1) || y > (image->_height - 1))
    {
        if(error) *error = 1;
        return;
    }

    red = red <= 255 ? red : 255;
    green = green <= 255 ? green : 255;
    blue = blue <= 255 ? blue : 255;

    RGB color = { red, green, blue };

    if(error) *error = 0;
    image->_pixels[x + (y * image->_width)] = color;
}

RGB pixmap_image_get_pixel(PixMapImage *image, unsigned int x, unsigned int y)
{
    if(x > (image->_width - 1) || y > (image->_height - 1))
    {
        RGB error_pixel = {-1, -1, -1};
        return error_pixel;
    }

    return image->_pixels[x + (y * image->_width)];
}

int pixmap_image_save(PixMapImage *image)
{
    FILE *image_file = fopen(image->_file_name, "w");

    if(!image_file)
        return -1;

    fprintf(image_file, "%s\n%d %d\n%d\n", "P3", image->_width, image->_height, image->_max_color_value);
    
    int i = 0;
    int w = 0;
    while(i < image->_width * image->_height)
    {        
        if(w > 2)
        {
            fprintf(image_file, "%d %d %d\n",
                    image->_pixels[i].red, image->_pixels[i].green, image->_pixels[i].blue);
            w = 0;
        } else {
            fprintf(image_file, "%d %d %d ",
                    image->_pixels[i].red, image->_pixels[i].green, image->_pixels[i].blue);
            
        }
 
        w++;
        i++;
    }

    fclose(image_file);

    return 0;
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

    free(image->_pixels);
    free(image);
}
