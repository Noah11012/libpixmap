#include "pixmap.h"

struct _PixMapImage
{
    char *_file_name;
    PixMapImageType _type;
    int _width;
    int _height;
    RGB *_pixels;
    int _max_color_value;
};

static int get_metadata_value(FILE *file);
static int read_ascii_pixel_values(PixMapImage *image, FILE *image_file);
static int read_8_bit_binary_pixel_values(PixMapImage *image, FILE *image_file);
static int read_16_bit_binary_pixel_values(PixMapImage *image,
                                           FILE *image_file);
static int write_ascii_file(PixMapImage *image, FILE *image_file);
static int write_8_bit_binary_file(PixMapImage *image, FILE *image_file);
static int write_16_bit_binary_file(PixMapImage *image, FILE *image_file);

PixMapImage *pixmap_image_new(char const *name, int width, int height,
                              int max_color_val, PixMapImageType type)
{
    type = (type == Text | type == Binary) ? type : Text;

    PixMapImage *new_image = malloc(sizeof(*new_image));

    if(!new_image)
        return 0;

    new_image->_width = width;
    new_image->_height = height;
    new_image->_max_color_value =
        max_color_val <= 65535 ? max_color_val : 65535;

    new_image->_pixels =
        malloc(sizeof(RGB) * (new_image->_width * new_image->_height));

    if(!new_image->_pixels)
    {
        free(new_image);
        return 0;
    }

    new_image->_file_name = name;
    new_image->_type = type;

    return new_image;
}

PixMapImage *pixmap_image_open(char const *name)
{
    FILE *image_file = fopen(name, "r+");

    if(!image_file)
        return 0;

    PixMapImage *new_image = malloc(sizeof(*new_image));

    if(!new_image)
    {
        fclose(image_file);
        return 0;
    }

    new_image->_file_name = name;

    unsigned char sig[3];
    fread(sig, sizeof(unsigned char), 2, image_file);

    if(sig[0] != 'P')
    {
        fclose(image_file);
        free(new_image);
        return 0;
    }

    new_image->_width = get_metadata_value(image_file);
    new_image->_height = get_metadata_value(image_file);
    new_image->_max_color_value = get_metadata_value(image_file);

    new_image->_width = new_image->_width > 0 ? new_image->_width : 1;
    new_image->_height = new_image->_height > 0 ? new_image->_height : 1;

    new_image->_pixels =
        malloc(sizeof(RGB) * (new_image->_width * new_image->_height));


    if(!new_image->_pixels)
    {
        fclose(image_file);
        free(new_image);
        return 0;
    }

    if(sig[1] == '3')
    {
        if(read_ascii_pixel_values(new_image, image_file) < 0)
            return 0;
    }
    else if(sig[1] == '6' && new_image->_max_color_value <= 255)
    {
        if(read_8_bit_binary_pixel_values(new_image, image_file) < 0)
            return 0;
    }
    else if(sig[1] == '6' && new_image->_max_color_value > 255)
    {
        if(read_16_bit_binary_pixel_values(new_image, image_file) < 0)
            return 0;
    }
    else
    {
        fclose(image_file);
        free(new_image);
        return 0;
    }

    if(!new_image)
    {
        fclose(image_file);
        free(new_image);
        return 0;
    }

    fclose(image_file);

    return new_image;
}

PixMapImage *pixmap_image_copy(PixMapImage const *image, char const *new_name,
                               PixMapImageType const type)
{
    PixMapImage *copy_image = pixmap_image_new(
        new_name, image->_width, image->_height, image->_max_color_value, type);

    if(!copy_image)
        return 0;

    int i = 0;
    while(i < copy_image->_width * copy_image->_height)
    {
        copy_image->_pixels[i] = image->_pixels[i];
        i++;
    }

    return copy_image;
}

RGB *pixmap_image_get_pixel_array(PixMapImage const *image)
{
    return image->_pixels;
}

void pixmap_image_set_pixel(PixMapImage *image, int x, int y, int red,
                            int green, int blue, int *error)
{
    if(x > (image->_width - 1) || y > (image->_height - 1) || x < 0 || y < 0 ||
       red < 0 || green < 0 || blue < 0)
    {
        *error = 1;
        return;
    }

    red = red <= image->_max_color_value ? red : image->_max_color_value;
    green = green <= image->_max_color_value ? green : image->_max_color_value;
    blue = blue <= image->_max_color_value ? blue : image->_max_color_value;

    RGB color = {red, green, blue};

    image->_pixels[x + (y * image->_width)] = color;
}

void pixmap_image_set_pixel_by_rgb(PixMapImage *image, int x, int y, RGB *rgb,
                                   int *error)
{
    pixmap_image_set_pixel(image, x, y, rgb->red, rgb->green, rgb->blue, error);
}

RGB pixmap_image_get_pixel(PixMapImage const *image, int x, int y)
{
    if(x > (image->_width - 1) || y > (image->_height - 1) || x < 0 || y < 0)
    {
        RGB error_pixel = {-1, -1, -1};
        return error_pixel;
    }

    return image->_pixels[x + (y * image->_width)];
}

int pixmap_image_save(PixMapImage const *image)
{
    if(!image->_file_name)
        return -1;

    FILE *image_file = fopen(image->_file_name, "w");

    if(!image_file)
        return -1;

    if(image->_type == Text)
        write_ascii_file(image, image_file);
    else if(image->_type == Binary && image->_max_color_value <= 255)
        write_8_bit_binary_file(image, image_file);
    else if(image->_type == Binary && image->_max_color_value > 255)
        write_16_bit_binary_file(image, image_file);

    fclose(image_file);

    return 0;
}

int pixmap_image_get_width(PixMapImage const *image)
{
    return image->_width;
}

int pixmap_image_get_height(PixMapImage const *image)
{
    return image->_height;
}

int pixmap_image_get_max_color_value(PixMapImage const *image)
{
    return image->_max_color_value;
}

PixMapImageType pixmap_image_get_type(PixMapImage const *image)
{
    return image->_type;
}

void pixmap_image_foreach_pixel(PixMapImage *image,
                                void (*func)(RGB pixel, void *func_arg),
                                void *arg)
{
    int total_pixels = image->_width * image->_height;
    for(int i = 0; i < total_pixels; i++) (*func)(image->_pixels[i], arg);
}

void pixmap_image_close(PixMapImage *image)
{
    if(!image)
        return;

    if(image->_pixels)
    {
        free(image->_pixels);
        image->_pixels = NULL;
    }

    free(image);
}

static int get_metadata_value(FILE *fin)
{
    int c, res = 0;
    int comment = 0;
    while((c = fgetc(fin)) != EOF)
    {
        if(c == '#')
            comment = 1;
        if(c == '\n')
            comment = 0;

        if(isdigit(c) && !comment)
        {
            ungetc(c, fin);
            fscanf(fin, "%d", &res);
            break;
        }
    }

    return res;
}

static int read_ascii_pixel_values(PixMapImage *image, FILE *image_file)
{
    int c;
    RGB pixel;
    unsigned int value_in = 0;
    int rgb_counter = 1;
    int file_pos = 0;
    int total_pixels = image->_width * image->_height;

    /* Read in the pixel values */
    while((c = fgetc(image_file)) != EOF)
    {
        value_in = 0;
        if(isdigit(c))
        {
            ungetc(c, image_file);
            if(rgb_counter > 3)
            {
                image->_pixels[file_pos] = pixel;
                file_pos++;
                rgb_counter = 1;
            }

            while((c = fgetc(image_file)) != EOF && c != ' ' && c != '\n')
            {
                value_in *= 10;
                value_in += (c - '0');
            }

            if(rgb_counter == 1)
                pixel.red = value_in;
            else if(rgb_counter == 2)
                pixel.green = value_in;
            else if(rgb_counter == 3)
                pixel.blue = value_in;

            rgb_counter++;
        }
    }

    if(file_pos > total_pixels)
    {
        free(image);
        image = NULL;
        fclose(image_file);

        return -1;
    }

    return 0;
}

static int read_8_bit_binary_pixel_values(PixMapImage *image, FILE *image_file)
{
    int total_pixels = image->_width * image->_height;
    uint8_t value_in[3];
    for(int i = 0; i < total_pixels; i++)
    {
        fread(value_in, sizeof(uint8_t), 3, image_file);

        if(ferror(image_file))
        {
            fclose(image_file);
            free(image);
            image = NULL;

            return -1;
        }

        image->_pixels[i] = (RGB){.red = (int)value_in[0],
                                  .green = (int)value_in[1],
                                  .blue = (int)value_in[2]};
    }

    return 0;
}

static int read_16_bit_binary_pixel_values(PixMapImage *image, FILE *image_file)
{
    int total_pixels = image->_width * image->_height;
    uint16_t value_in[3];
    for(int i = 0; i < total_pixels; i++)
    {
        fread(value_in, sizeof(uint16_t), 3, image_file);

        if(ferror(image_file))
        {
            fclose(image_file);
            free(image);
            image = NULL;

            return -1;
        }

        image->_pixels[i] = (RGB){.red = (int)ntohs(value_in[0]),
                                  .green = (int)ntohs(value_in[1]),
                                  .blue = (int)ntohs(value_in[2])};
    }

    return 0;
}

static int write_ascii_file(PixMapImage *image, FILE *image_file)
{
    fprintf(image_file, "%s\n%d %d\n%d\n", "P3", image->_width, image->_height,
            image->_max_color_value);

    int i = 0;
    int w = 0;
    while(i < image->_width * image->_height)
    {
        if(w > 2)
        {
            fprintf(image_file, "%d %d %d\n", image->_pixels[i].red,
                    image->_pixels[i].green, image->_pixels[i].blue);
            w = 0;
        }
        else
        {
            fprintf(image_file, "%d %d %d ", image->_pixels[i].red,
                    image->_pixels[i].green, image->_pixels[i].blue);
        }

        w++;
        i++;
    }
}

static int write_8_bit_binary_file(PixMapImage *image, FILE *image_file)
{
    uint8_t *temp_pixels =
        malloc(sizeof(uint8_t) * image->_width * image->_height * 3);

    if(!temp_pixels)
    {
        fclose(image_file);
        return -1;
    }

    int i = 0;
    for(int y = 0; y < image->_height; y++)
    {
        for(int x = 0; x < image->_width; x++)
        {
            temp_pixels[i++] =
                (uint8_t)image->_pixels[x + (y * image->_width)].red;
            temp_pixels[i++] =
                (uint8_t)image->_pixels[x + (y * image->_width)].green;
            temp_pixels[i++] =
                (uint8_t)image->_pixels[x + (y * image->_width)].blue;
        }
    }

    fprintf(image_file, "%s\n%d %d\n%d", "P6", image->_width, image->_height,
            image->_max_color_value);
    fwrite(temp_pixels, sizeof(uint8_t), image->_width * image->_height * 3,
           image_file);

    free(temp_pixels);
}

static int write_16_bit_binary_file(PixMapImage *image, FILE *image_file)
{
    uint16_t *temp_pixels =
        malloc(sizeof(uint16_t) * image->_width * image->_height * 3);

    if(!temp_pixels)
    {
        fclose(image_file);
        return -1;
    }

    int i = 0;
    for(int y = 0; y < image->_height; y++)
    {
        for(int x = 0; x < image->_width; x++)
        {
            temp_pixels[i++] =
                htons(image->_pixels[x + (y * image->_width)].red);
            temp_pixels[i++] =
                htons(image->_pixels[x + (y * image->_width)].green);
            temp_pixels[i++] =
                htons(image->_pixels[x + (y * image->_width)].blue);
        }
    }

    fprintf(image_file, "%s\n%d %d\n%d", "P6", image->_width, image->_height,
            image->_max_color_value);
    fwrite(temp_pixels, sizeof(uint16_t), image->_width * image->_height * 3,
           image_file);

    free(temp_pixels);
}
