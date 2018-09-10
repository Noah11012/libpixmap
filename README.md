# PixMap library in C
Libpixmap is a library to read and write pixmap image formats with a simple to use API.

This library is a work in progress. Any help would be appreciated.

## Issues
This is a list of issues needed to be fixed to release the first version of this library.

Level 1 issues don't necessarily have to be completed for the library to be released. These issues are minor and can be resolved after the release.

Level 2 issues should be fixed but are medium in priority. These types of issues mean an important part of the library is not functioning, an API design decision, or a minor to medium bug is present.

Level 3 issues *MUST* be completed before the release of this library. These issues are open when a fundemental part of the library is not complete. E.g. `pixmap_image_open()` not working.

| Level | Issue | Complete |
|-------|-------|--------- |
| 3     | `pixmap_image_open()` does not yet parse the pixel information into the `_pixels` array | No |
| 2     | `pixmap_image_get_pixel()` currently returns a pointer to an `RGB` that corresponds to the pixel in the image. If the user changes any of the members in the `RGB` variable and calls `pixmap_image_save()` the pixel will change to one the user provided. It would better only to have the pixels changed through the `pixmap_image_set_pixel()` function. | No |

## Build

`git clone https://github.com/Noah11012/libpixmap.git`

`cd /path/to/libpixmap`

`mkdir build && cd build`

`cmake ..`

If you want to change the install prefix, enter the following:

`cmake .. -DCMAKE_INSTALL_PREFIX=/path/to/install/prefix`

`make`

## Usage

// Complete this section