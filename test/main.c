#include "../src/pixmap.h"
#include "../src/pixmap_filters.h"

int test1()
{
    PixMapImage *image = pixmap_image_new("test.ppm", 100, 100, 255, Text);

    if(!image) return -1;

    int status = 0;

    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j < 100; j++)
        {
            pixmap_image_set_pixel(image, j, i, j, i, 0, &status);

            if(status) return -1;
        }
    }

    PixMapImage *image_copy = pixmap_image_copy(image, "test_copy.ppm", Text);
    if(!image_copy) return -1;

    if(pixmap_image_save_rgb(image) != 0) return -1;

    if(pixmap_image_save_rgb(image_copy) != 0) return -1;

    pixmap_image_close(image);
    pixmap_image_close(image_copy);

    return 0;
}

int test2()
{
    PixMapImage *image_in = pixmap_image_open("test_copy.ppm");

    if(!image_in) return -1;

    PixMapImage *image_out =
        pixmap_image_copy(image_in, "test_copy2.ppm", Text);

    if(!image_out) return -1;

    int status = pixmap_image_save_rgb(image_out);

    if(status != 0) return -1;

    pixmap_image_close(image_in);
    pixmap_image_close(image_out);
    return 0;
}

int test3()
{
    PixMapImage *image =
        pixmap_image_new("test_binary.ppm", 100, 100, 255, Binary);

    if(!image) return -1;

    for(int y = 0; y < pixmap_image_get_height(image); y++)
    {
        for(int x = 0; x < pixmap_image_get_width(image); x++)
        {
            pixmap_image_set_pixel(image, x, y, 255, y, x, NULL);
        }
    }

    pixmap_image_save_rgb(image);

    pixmap_image_close(image);
    return 0;
}

int test4(void)
{
    PixMapImage *image = pixmap_image_open("test_binary.ppm");

    if(!image) return -1;

    PixMapImage *image_out =
        pixmap_image_copy(image, "test_binary2.ppm", Binary);

    if(!image_out) return -1;


    if(pixmap_image_save_rgb(image_out) != 0) return -1;

    pixmap_image_close(image);
    pixmap_image_close(image_out);

    return 0;
}

int test5()
{
    PixMapImage *image =
        pixmap_image_new("test_image.ppm", 100, 100, 255, Text);

    if(!image) return -1;

    PixMapImage *copy_image =
        pixmap_image_copy(image, "test_image_copy.ppm", Text);

    if(!copy_image) return -1;

    if(pixmap_image_get_pixel_array(image) ==
       pixmap_image_get_pixel_array(copy_image))
        return -1;

    return 0;
}

int test6()
{
    PixMapImage *image = pixmap_image_new("test6_image.ppm", 50, 50, 256, Text);
    if(!image) return -1;
    int *error = NULL;

    for(int y = 0; y < 50; y++)
    {
        for(int x = 0; x < 50; x++)
        {
            pixmap_image_set_pixel(image, x, y, x, y, 8, error);
            if(error) return -1;
        }
    }

    pixmap_filter_brightness(image, -9, error);
    if(error) return -1;
    pixmap_image_save_rgb(image);
}

int test7()
{
    PixMapImage *in = pixmap_image_open("test6_image.ppm");
    PixMapImage *out = pixmap_image_copy(in, "test7_image.ppm", Text);
    if(!out)
	return -1;
    int error = 0;
    pixmap_filter_desaturate_average(out, &error);
    if(error)
	return -1;
    if(pixmap_image_save_rgb(out) != 0)
	return -1;
    pixmap_image_close(in);
    pixmap_image_close(out);
    return 0;
}

int test8()
{
    PixMapImage *in = pixmap_image_open("test7_image.ppm");
    PixMapImage *out = pixmap_image_copy(in, "test8_image.pgm", Binary);
    if(!out)
	return -1;
    if(pixmap_image_save_greyscale(out) != 0)
	return -1;
    pixmap_image_close(in);
    pixmap_image_close(out);
    return 0;
}

int main()
{
    if(test1() != 0) return 1;

    if(test2() != 0) return 2;

    if(test3() != 0) return 3;

    if(test4() != 0) return 4;

    if(test5() != 0) return 5;

    if(test6() != 0) return 6;

    if(test7() != 0)
	return 7;

    if(test8() != 0)
	return 8;

    return 0;
}
