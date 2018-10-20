add_library(libpixmapimage SHARED pixmap.c pixmap_filters.c pixmap_draw.c)
target_link_libraries(libpixmapimage PUBLIC m)