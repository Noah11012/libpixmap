#include <stdio.h>
#include "pixmap.h"
    
int main(void)
{
    PixMapImage *image = 0;
    pixmap_image_open(&image, "../test.ppm");

    if(!image)
        return -1;

    printf("Width: %d\nHeight: %d\n", pixmap_image_width(image), pixmap_image_height(image));
}
