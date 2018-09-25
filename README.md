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

Because this library only contains a header and source file, you can simply include pixmap.h and add pixmap.c to the list of files needing to be built.

Example:

`clang -o program main.c another_file.c pixmap.c`

In main.c:

```c
#include "pixmap.h"

int main(int argc, char *argv[])
{
    ...
}
```

## Documentation
### `pixmap_image_new(char const *name, int width, int height, int max_color_val)`

Creates a new at the path `name` and with the dimensions of `with` x `height` and the maximum color value of `max_color_val`. `max_color_val` is clamped at 255. Returns 0 on failure.

### `pixmap_image_open(char const *name)`

Opens an existing image at the path `name`. Returns a `PixMapImage` on success. Otherwise, returns 0.