# PixMap library in C

## What is libpixmap?

Libpixmap is a library written in pure C that aims to provide an easy and convient API for reading and writing PPM files.

Features:

* Open PPM images
* Create new blank PPM images
* Set and retrieve color values for specific pixels
* Set and get all pixels

## Quick Start

This library is by design very simple. Only a header and source file. Include the header and add the source file to the list of files to build.

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
