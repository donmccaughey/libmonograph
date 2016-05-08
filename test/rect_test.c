#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <monograph/monograph.h>


static void
test_alloc_string(void)
{
    struct mg_rect rect = mg_rect_make(
            mg_point_make(1, 2), mg_size_make(3, 4));
    int length = 0;
    char *s = mg_rect_alloc_string(&rect, &length);
    assert(s);
    assert(strcmp(s, "(1, 2) 3x4") == 0);
    assert(length == 10);
    free(s);
}


static void
test_from_string(void)
{
    struct mg_rect rect = mg_rect_make(
            mg_point_make(0, 0), mg_size_make(0, 0));
    char const s[] = "  ( 1,2 )  3 x 4 \n";
    int length = 0;
    int result = mg_rect_from_string(s, &rect, &length);
    assert(result == 0);
    assert(rect.point.x == 1);
    assert(rect.point.y == 2);
    assert(rect.size.width == 3);
    assert(rect.size.height == 4);
    assert(length == 16);
}


int
main(int argc, char *argv[])
{
    test_alloc_string();
    test_from_string();
    return EXIT_SUCCESS;
}

