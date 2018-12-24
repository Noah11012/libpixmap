#include "../pixmap.c"
#include <stdio.h>

#define TEST_IMAGE_WIDTH 30
#define TEST_IMAGE_HEIGHT 20

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

    if(!(pixmap_image_width(image) == TEST_IMAGE_WIDTH && pixmap_image_height(image) == TEST_IMAGE_HEIGHT))
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
}
