#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <monograph/monograph.h>


static void
test_alloc_string(void)
{
    struct mg_point point = mg_point_make(0, 0);
    int length = 0;
    char *s = mg_point_alloc_string(point, &length);
    assert(s);
    assert(strcmp(s, "(0, 0)") == 0);
    assert(length == 6);
    free(s);
}


static void
test_from_string(void)
{
    struct mg_point point = mg_point_make(0, 0);
    char const s[] = "  ( 1,2 ) \n";
    int length = 0;
    int result = mg_point_from_string(s, &point, &length);
    assert(result == 0);
    assert(point.x == 1);
    assert(point.y == 2);
    assert(length == 9);
}


static void
test_from_string_when_invalid(void)
{
    struct mg_point point = mg_point_make(0, 0);
    char const s[] = " (1x2)";
    int length = 0;
    int result = mg_point_from_string(s, &point, &length);
    assert(result == -1);
}


int
main(int argc, char *argv[])
{
    test_alloc_string();
    test_from_string();
    test_from_string_when_invalid();
    return EXIT_SUCCESS;
}

