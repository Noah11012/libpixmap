# PixMap library in C

## What is libpixmap?

Libpixmap is a library written in pure C that aims to provide an easy and convient API for reading and writing PPM files.

Features:

* Open PPM images
* Create blank PPM images
* Set and retrieve color values for specific pixels
* Set and get all pixels

## Example

```cpp
#include <stdio.h>
#include "pixmap.h"

int main(void)
{
    PixMapImage *image;
    pixmap_image_open(&image, "path/to/image.ppm");

    if(!image)
    {
        printf("Error: failed to open image!\n");
        return 1;
    }

    printf("Image width: %d\n", image->width);
    printf("Image height: %d\n", image->height);

    // Retrieve individual pixels

    PixMapRGB pixel;

    // Returns -1 if the coordinates supplied are out of bounds
    pixmap_image_get_pixel(image, 100, 100, &pixel);

    printf("Red: %d\n", pixel.red);
    printf("Green: %d\n", pixel.green);
    printf("Blue: %d\n", pixel.blue);

    // Set individual pixels

    PixMapRGB new_pixel;
    new_pixel.red = 50;
    new_pixel.green = 150;
    new_pixel.blue = 200;

    pixmap_image_set_pixel(image, 100, 100, &new_pixel);

    // Clean up

    pixmap_image_free(image);
}
```

## Quick Start

Libpixmap can be used two ways: with and without clibs.

### With Clibs

[Clibs](https://github.com/clibs/clib) is a package manager for small C libraries. To install with Clibs, use the following command:

`clib install Noah11012/libpixmap`

### Without Clibs

This library is by design very simple. Only a header and a source file. Include the header and add the source file to the list of files to build.

Example:

```cpp
// main.c
#include "pixmap.h"

int main()
{
    // Code
}
```

Compile with clang:

```
clang -o program main.c pixmap.c
```

Of course, if you use a build system like Make or a generator like that of CMake, then simply add pixmap.c to all the other files to be built.
