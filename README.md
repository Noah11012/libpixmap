# PixMap library in C
Libpixmap is a library to read and write pixmap image formats with a simple to use API.

This library is a work in progress. Any help would be appreciated.

## Issues
This is a list of issues needing to be resolved to release the first version of this library.

Level 1 issues don't necessarily have to be completed for the library to be released. Usually they pertain to refactoring of the code. These issues are minor and can be resolved after the release.

Level 2 issues should be fixed but are medium in priority. These types of issues mean an important part of the library is not functioning, an API design decision, or a minor to medium bug is present.

Level 3 issues *MUST* be completed before the release of this library. These issues are open when a fundemental part of the library is not complete. E.g. `pixmap_image_open()` not working.

| Level | Issue | Complete |
|-------|-------|--------- |
| 3     | `pixmap_image_open()` does not yet parse the pixel information into the `_pixels` array | No |
| 2     | `pixmap_image_get_pixel()` currently returns a pointer to an `RGB` that corresponds to the pixel in the image. If the user changes any of the members in the `RGB` variable and calls `pixmap_image_save()` the pixel will change to one the user provided. It would better only to have the pixels changed through the `pixmap_image_set_pixel()` function. | No |
| 1     | An inconsistent error mechanism exists in the library. Some functions return 0 to signify an error happened. Other functions that have void as a return type like `pixmap_image_set_pixel()` simply do nothing if a condition was not met or an error occurred. How does the user know if something went awry? They can't and this problem should be fixed eventually. | No |

## Build

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

## Usage

// Complete this section