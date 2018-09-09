#include "../src/pixmap.h"

int main()
{
    PixMapImage *image = pixmap_image_new("/home/noah/Desktop/test.ppm", 200, 200, 255);

    if(!image)
    {
        printf("Failed to create image!\n");
        return -1;
    }

    for(int i = 0; i < 200; i++)
    {
        for(int j = 0; j < 200; j++)
        {
            pixmap_image_set_pixel(image, i, j, 255, 0, 0);
        }
    }

    printf("Width: %d\nHeight: %d\n", pixmap_image_get_width(image),
                                      pixmap_image_get_height(image));

    pixmap_image_save(image);
    pixmap_image_close(image);
}