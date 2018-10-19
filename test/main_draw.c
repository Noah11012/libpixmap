#include "../src/pixmap_draw.h"

int test1()
{
    PixMapImage *image = pixmap_image_new("test_draw.ppm", 100, 100, 255, Text);

    if(!image)
        return -1;
    
    RGB red = {255, 0, 0};

    if(pixmap_image_draw_line(image, &red, 10, 10, 50, 50) < 0)
        return -1;
    
    pixmap_image_save(image);
    
    return 0;
}

int main()
{
    if(test1() != 0)
        return -1;
    
    return 0;
}