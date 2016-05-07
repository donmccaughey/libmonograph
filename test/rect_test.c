#include <assert.h>
#include <stdlib.h>

#include <monograph/monograph.h>


static void
test_is_top_left(void)
{
    struct mg_rect rect = mg_rect_make(
            mg_point_make(0, 1), mg_size_make(2, 3));

    assert(mg_rect_is_top_left(&rect, mg_point_make(0, 1)));
    assert(!mg_rect_is_top_left(&rect, mg_point_make(1, 1)));
    assert(!mg_rect_is_top_left(&rect, mg_point_make(0, 0)));
}


static void
test_is_top_right(void)
{
    struct mg_rect rect = mg_rect_make(
            mg_point_make(0, 1), mg_size_make(2, 3));

    assert(mg_rect_is_top_right(&rect, mg_point_make(1, 1)));
    assert(!mg_rect_is_top_right(&rect, mg_point_make(0, 1)));
    assert(!mg_rect_is_top_right(&rect, mg_point_make(1, 0)));
}


static void
test_is_bottom_left(void)
{
    struct mg_rect rect = mg_rect_make(
            mg_point_make(0, 1), mg_size_make(2, 3));

    assert(mg_rect_is_bottom_left(&rect, mg_point_make(0, 3)));
    assert(!mg_rect_is_bottom_left(&rect, mg_point_make(0, 1)));
    assert(!mg_rect_is_bottom_left(&rect, mg_point_make(1, 3)));
}


static void
test_is_bottom_right(void)
{
    struct mg_rect rect = mg_rect_make(
            mg_point_make(0, 1), mg_size_make(2, 3));

    assert(mg_rect_is_bottom_right(&rect, mg_point_make(1, 3)));
    assert(!mg_rect_is_bottom_right(&rect, mg_point_make(0, 3)));
    assert(!mg_rect_is_bottom_right(&rect, mg_point_make(1, 0)));
}


int
main(int argc, char *argv[])
{
    test_is_top_left();
    test_is_top_right();
    test_is_bottom_left();
    test_is_bottom_right();
    return EXIT_SUCCESS;
}

