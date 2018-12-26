#include "../pixmap.c"
#include <stdio.h>

#define TEST_IMAGE_WIDTH 30
#define TEST_IMAGE_HEIGHT 20
#define TEST_IMAGE_MAX_COLOR_VALUE 255

int test1()
{
    PixMapImage *image = 0;
    pixmap_image_open(&image, "../test.ppm");

    if(!image)
        return -1;

    return 0;
}

int test2()
{
    PixMapImage *image = 0;
    pixmap_image_open(&image, "../test.ppm");

    if(!image)
        return -1;

    if(!(pixmap_image_width(image) == TEST_IMAGE_WIDTH &&
         pixmap_image_height(image) == TEST_IMAGE_HEIGHT) &&
         pixmap_image_max_color_value(image) == TEST_IMAGE_MAX_COLOR_VALUE)
        return -1;

    return 0;
}

int test3()
{
    PixMapImage *image = 0;
    pixmap_image_open(&image, "../test.ppm");

    if(!image)
        return -1;

    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;

    pixmap_image_get_pixel(image, 0, 0, &r, &g, &b);
    if(!(r == 0 && g == 255 && b == 0))
        return -1;

    pixmap_image_get_pixel(image, TEST_IMAGE_WIDTH - 1, 0, &r, &g, &b);
    if(!(r == 0 && g == 255 && b == 0))
        return -1;

    pixmap_image_get_pixel(image, 0, TEST_IMAGE_HEIGHT - 1, &r, &b, &b);
    if(!(r == 0 && g == 255 && b == 0))
        return -1;

    pixmap_image_get_pixel(image, TEST_IMAGE_WIDTH - 1, TEST_IMAGE_HEIGHT - 1, &r, &g, &b);
    if(!(r == 0 && g == 255 && b == 0))
        return -1;

    return 0;
}

#define RUN_TEST(test_name) \
    if(test_name () != -1) \
        printf(#test_name " passed!\n"); \
    else \
        printf(#test_name " FAILED!\n"); \

int main(void)
{
    RUN_TEST(test1);
    RUN_TEST(test2);
    RUN_TEST(test3);
}
