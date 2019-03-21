#include "pixmap.h"
#include <stdio.h>

int main(void)
{
    PixMapImage *image = 0;
    pixmap_image_open(
        &image, "/home/noah/Desktop/Documents/Projects/libpixmap/test.ppm");

    if(!image)
        return 1;

    PixMapRGB color = {0, 0, 255};
    pixmap_image_set_pixel(image, pixmap_image_get_width(image) - 1,
                           pixmap_image_get_height(image) - 1, &color);

    pixmap_image_save(image);
}