#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <monograph/monograph.h>


static void
test_alloc(void)
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


static void
test_draw_when_box_fits_canvas(void)
{
    struct mg_size size = mg_size_make(10, 4);
    struct mg_rect rect = mg_rect_make(mg_point_make(0, 0), size);
    struct mg_box *box = mg_box_alloc(&rect, "a box");
    struct mg_canvas *canvas = mg_canvas_alloc(size);

    mg_box_draw(box, canvas);

    char const expected_text[] =
        "+--------+\n"
        "| a box  |\n"
        "|        |\n"
        "+--------+\n"
        ;
    assert(strcmp(canvas->text, expected_text) == 0);

    mg_box_free(box);
    mg_canvas_free(canvas);
}


static void
test_alloc_string(void)
{
    struct mg_rect rect = mg_rect_make(
            mg_point_make(1, 2), mg_size_make(3, 4));
    struct mg_box *box = mg_box_alloc(&rect, "a box");
    int length = 0;
    char *s = mg_box_alloc_string(box, &length);
    assert(s);
    assert(strcmp(s, "box (1, 2) 3x4 a box\n") == 0);
    assert(length == 21);
    free(s);
    mg_box_free(box);
}


static void
test_alloc_from_string(void)
{
    char const s[] = "\tbox (1 , 2) 3x 4  a box \n";
    int length = 0;
    struct mg_box *box = mg_box_alloc_from_string(s, &length);
    assert(box);
    assert(box->rect.point.x == 1);
    assert(box->rect.point.y == 2);
    assert(box->rect.size.width == 3);
    assert(box->rect.size.height == 4);
    assert(strcmp(box->title, "a box") == 0);
    assert(length == 26);
    mg_box_free(box);
}


int
main(int argc, char *argv[])
{
    test_alloc();
    test_draw_when_box_fits_canvas();
    test_alloc_string();
    test_alloc_from_string();
    return EXIT_SUCCESS;
}

