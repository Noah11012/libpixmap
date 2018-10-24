# PixMap library in C
Libpixmap is a library to read and write pixmap image formats with a simple to use API.

## Getting Started

`git clone https://github.com/Noah11012/libpixmap.git`

`cd /path/to/libpixmap`

`mkdir build && cd build`

`cmake ..`

If you want to change the install prefix, enter the following:

`cmake .. -DCMAKE_INSTALL_PREFIX=/path/to/install/prefix`

`make`

This library contains one header and one source file. Two headers and two source files that are optional but provide filters and drawing capabilities.

Example:

`clang -o program main.c another_file.c pixmap.c pixmap_filters.c pixmap_draw.c`

In main.c:

```c
#include "pixmap.h"
#include "pixmap_filters.h"
#include "pixmap_draw.h"

int main(int argc, char *argv[])
{
    ...
}
```

## Documentation
#### pixmap_image_new(char const *name, int width, int height, int max_color_val, PixMapImageType type)

Creates a new `PixMapImage` at the path `name` and with the dimensions of `width` x `height` and the maximum color value of `max_color_val` with the PPM image type of `type`. `type` can either be `Text` or `Binary`. `max_color_val` is clamped at 65535. A `max_color_val` of 255 or less will create an 8-bit image, while a `max_color_val` between 256 and 65535 will create a 16-bit image. Free with `pixmap_image_close()`. Returns 0 on failure.

#### pixmap_image_close(PixMapImage *image)

Frees and closes all resources associated with `image`.

#### pixmap_image_open(char const *name)

Opens an existing image at the path `name`. Free with `pixmap_image_close()`. Returns a `PixMapImage` on success. Otherwise, returns 0.

#### pixmap_image_copy(PixMapImage *image, char const *new_name, PixMapImageType type)

Copies an existing `PixMapImage` under the new name `new_name` with PPM image type of `type` `type` can either be `Text` or `Binary`. Does not actually write to disk until `pixmap_image_save()` is called. Free with `pixmap_image_close()`. Returns the copy on success but 0 on failure.

#### pixmap_image_get_pixel_array(PixMapImage *image)

Returns the underlying array of `RGB` values from a given `PixMapImage`.
DO NOT free this array with `free()`. Use `pixmap_image_close()` on the `PixMapImage`
instead. Any changes to the pixel array can be saved using `pixmap_image_save()`.

#### pixmap_image_set_pixel(PixMapImage *image, int x, int y, int red, int green, int blue, int *error)

Sets an individual pixel from the image to a specified color. If the provided coordinate is out of bounds, then `error` will be set to 1 if a pointer to an `int` was given.

#### pixmap_image_set_pixel_by_rgb(PixMapImage *image, int x, int y, RGB *rgb, int *error)

Sets an individual pixel from the image to a color specified by the `RGB` object passed to the function. If the provided coordinate is out of bounds, then `error` will be set to 1 if a pointer to an `int` was given.

#### pixmap_image_get_pixel(PixMapImage *image, int x, int y)

Gets an individual pixel from the image at the specified coordinate and returns an `RGB` value. If the specified coordinate is out of bounds, then all the values in the `RGB` value will be set to -1.

#### pixmap_image_save(PixMapImage *image)

Saves a `.ppm` file of the given image. The filename is determined from the supplied `name` at the time of image creation. Returns 0 on success and -1 on failure.

#### pixmap_image_get_width(PixMapImage *image)

Returns the width of the given image object.

#### pixmap_image_get_height(PixMapImage *image)

Returns the height of the given image object.

#### pixmap_image_get_max_color_value(PixMapImage *image)

Returns the max color value of the given image object.

#### pixmap_image_get_type(PixMapImage *image)

Returns the type of the given image object. The valid types are `Text` for ASCII-encoded files and `Binary` for binary-encoded files.

#### pixmap_imaage_foreach_pixel(PixMapImage *image, void (*func)(RGB pixel, void *arg), void *func_arg)

Applies a given transform to each pixel in an image object. Takes a function of the form `void (*func)(RGB pixel, void *arg)`, that is a function returning `void` that takes an `RGB` and a `void *` argument. The argument `func_arg` is a `void *` that can be used to pass any value or `struct` of values to the given function.
