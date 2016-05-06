#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <monograph/monograph.h>


static void
test_box_alloc(void)
{
    struct mg_rect rect = mg_rect_make(
            mg_point_make(0, 1), mg_size_make(2, 3));
    struct mg_box *box = mg_box_alloc(&rect, "a box");
    
    assert(box);
    assert(box->rect.point.x == 0);
    assert(box->rect.point.y == 1);
    assert(box->rect.size.width == 2);
    assert(box->rect.size.height == 3);
    assert(strcmp(box->title, "a box") == 0);

    mg_box_free(box);
}


int
main(int argc, char *argv[])
{
    test_box_alloc();
    return EXIT_SUCCESS;
}

