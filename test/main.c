#include "../src/pixmap.h"

int test1()
{
    PixMapImage *image = pixmap_image_new("test.ppm", 100, 100, 255);

    if(!image)
        return -1;
    
    int status = 0;

    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j < 100; j++)
        {
            pixmap_image_set_pixel(image, j, i, j, i, 0, &status);

            if(status)
                return -1;
        }
    }

    PixMapImage *image_copy = pixmap_image_copy(image, "test_copy.ppm");
    if(!image_copy)
	return -1;

    if(pixmap_image_save(image) != 0)
        return -1;

    if(pixmap_image_save(image_copy) != 0)
        return -1;

    pixmap_image_close(image);
    pixmap_image_close(image_copy);

    return 0;
}

int test2()
{
    PixMapImage *image_in = pixmap_image_open("test_copy.ppm");
    if(!image_in) {
	return -1;
    }
    PixMapImage *image_out = pixmap_image_copy(image_in, "test_copy2.ppm");
    if(!image_out) {
	return -1;
    }
    int status = pixmap_image_save(image_out);
    if(status != 0) {
	return -1;
    }
    return 0;
}


int main()
{
    if(test1() != 0)
        return -1;
    if(test2() != 0)
	return -1;
    return 0;
}
