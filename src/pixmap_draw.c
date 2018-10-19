#include "pixmap_draw.h"

int pixmap_draw_line(PixMapImage *image, RGB *rgb, int x1, int y1, int x2, int y2)
{
    /* Make sure the line is drawn ascending in x so the loop doesn't go
       on forever */
    if(x1 > x2)
    {
	int temp = x1;
	x1 = x2;
	x2 = temp;

        temp = y1;
	y1 = y2;
	y2 = temp;
    }
    
    int x = x1;
    double y = y1;
    double slope = (double) (y2 - y1) / (x2 - x1);

    int status = 0;

    for(; x != x2; x += 1, y += slope)
	{
	    pixmap_image_set_pixel_by_rgb(image, x, round(y), rgb, &status);

	    if(status)
		return -1;
	}
    /* Set the last pixel */
    pixmap_image_set_pixel_by_rgb(image, x2, y2, rgb, &status);
    if(status)
	return -1;

    return 0;
}
