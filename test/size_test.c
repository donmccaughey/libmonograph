#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <monograph/monograph.h>


static void
test_alloc_string(void)
{
    struct mg_size size = mg_size_make(3, 4);
    int length = 0;
    char *s = mg_size_alloc_string(size, &length);
    assert(s);
    assert(strcmp(s, "3x4") == 0);
    assert(length == 3);
    free(s);
}


static void
test_from_string(void)
{
    struct mg_size size = mg_size_make(0, 0);
    char const s[] = "  3 x 4 \n";
    int length = 0;
    int result = mg_size_from_string(s, &size, &length);
    assert(result == 0);
    assert(size.width == 3);
    assert(size.height == 4);
    assert(length == 7);
}


int
main(int argc, char *argv[])
{
    test_alloc_string();
    return EXIT_SUCCESS;
}

