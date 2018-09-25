#include "../src/pixmap.h"

int main()
{
    PixMapImage *image = pixmap_image_new("test.ppm", 2, 2, 255);

    if(!image)
    {
        printf("Failed to create image!\n");
        return -1;
    }

    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            pixmap_image_set_pixel(image, i, j, 255, 255, 255, 0);
        }
    }

    printf("Width: %d\nHeight: %d\nMaximum color value: %d\n", pixmap_image_get_width(image),
                                                               pixmap_image_get_height(image),
                                                               pixmap_image_get_max_color_value(image));

    RGB *color = pixmap_image_get_pixel(image, 0, 0);
    printf("Color: %d %d %d\n", rgb_get_red(color), rgb_get_green(color), rgb_get_blue(color));

    RGB *color2 = pixmap_image_get_pixel(image, 1, 1);
    printf("Color: %d %d %d\n", rgb_get_red(color2), rgb_get_green(color2), rgb_get_blue(color2));

    RGB *color3 = pixmap_image_get_pixel(image, 2, 2);
    if(!color3) printf("Out of bounds!\n");

    pixmap_image_save(image);
    pixmap_image_close(image);

    PixMapImage *image2 = pixmap_image_open("test.ppm");

    if(!image2)
    {
        printf("Could not open image!\n");
        return 0;
    }

    printf("Width: %d\nHeight: %d\nMaximum color value: %d\n",
           pixmap_image_get_width(image2),
           pixmap_image_get_height(image2),
           pixmap_image_get_max_color_value(image2));
    
    printf("Printing _pixels\n");
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            RGB *pixel = pixmap_image_get_pixel(image2, j, i);
            printf("%u %u %u\n", rgb_get_red(pixel), rgb_get_green(pixel), rgb_get_blue(pixel));
        }
    }

    pixmap_image_close(image2);
}