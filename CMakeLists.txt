project(libmonograph)
cmake_minimum_required(VERSION 3.8)
set(CMAKE_C_STANDARD 99)
include_directories(
        src
        tmp/src/monograph
)


add_definitions(
        -D_BSD_SOURCE
        -D_GNU_SOURCE
)


add_library(monograph
        src/monograph/box.c
        src/monograph/box.h
        src/monograph/canvas.c
        src/monograph/canvas.h
        src/monograph/graph.c
        src/monograph/graph.h
        src/monograph/monograph.h
        src/monograph/point.c
        src/monograph/point.h
        src/monograph/rect.c
        src/monograph/rect.h
        src/monograph/size.c
        src/monograph/size.h
        tmp/src/monograph/config.h
        )


add_executable(box_test test/box_test.c)
target_link_libraries(box_test monograph)


add_executable(canvas_test test/canvas_test.c)
target_link_libraries(canvas_test monograph)


add_executable(graph_test test/graph_test.c)
target_link_libraries(graph_test monograph)


add_executable(point_test test/point_test.c)
target_link_libraries(point_test monograph)


add_executable(rect_test test/rect_test.c)
target_link_libraries(rect_test monograph)


add_executable(size_test test/size_test.c)
target_link_libraries(size_test monograph)
