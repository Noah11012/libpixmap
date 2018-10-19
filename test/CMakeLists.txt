add_executable(test main.c)
target_link_libraries(test PUBLIC libpixmapimage)

add_executable(test_draw main_draw.c)
target_link_libraries(test_draw PUBLIC libpixmapimage)