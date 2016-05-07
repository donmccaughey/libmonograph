#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <monograph/monograph.h>


static void
test_alloc(void)
{
    struct mg_size size = mg_size_make(10, 4);
    struct mg_canvas *canvas = mg_canvas_alloc(size);

    assert(canvas);
    assert(canvas->size.width == 10);
    assert(canvas->size.height = 4);
    assert(canvas->text);

    char const expected_text[] = 
        "          \n"
        "          \n"
        "          \n"
        "          \n"
        ;
    assert(strcmp(canvas->text, expected_text) == 0);

    assert(mg_canvas_get_text_length(canvas) == 44);

    mg_canvas_free(canvas);
}


static void
test_set_char_at(void)
{
    struct mg_size size = mg_size_make(10, 4);
    struct mg_canvas *canvas = mg_canvas_alloc(size);

    int result = mg_canvas_set_char_at(canvas, 'x', mg_point_make(0, 0));
    assert(result == 0);
    char const expected_text1[] = 
        "x         \n"
        "          \n"
        "          \n"
        "          \n"
        ;
    assert(strcmp(canvas->text, expected_text1) == 0);

    result = mg_canvas_set_char_at(canvas, 'y', mg_point_make(1, 1));
    assert(result == 0);
    char const expected_text2[] = 
        "x         \n"
        " y        \n"
        "          \n"
        "          \n"
        ;
    assert(strcmp(canvas->text, expected_text2) == 0);

    result = mg_canvas_set_char_at(canvas, 'z', mg_point_make(8, 2));
    assert(result == 0);
    char const expected_text3[] = 
        "x         \n"
        " y        \n"
        "        z \n"
        "          \n"
        ;
    assert(strcmp(canvas->text, expected_text3) == 0);

    result = mg_canvas_set_char_at(canvas, '!', mg_point_make(9, 3));
    assert(result == 0);
    char const expected_text4[] = 
        "x         \n"
        " y        \n"
        "        z \n"
        "         !\n"
        ;
    assert(strcmp(canvas->text, expected_text4) == 0);

    result = mg_canvas_set_char_at(canvas, '*', mg_point_make(-1, 1));
    assert(result == -1);

    result = mg_canvas_set_char_at(canvas, '*', mg_point_make(10, 1));
    assert(result == -1);

    result = mg_canvas_set_char_at(canvas, '*', mg_point_make(0, -1));
    assert(result == -1);

    result = mg_canvas_set_char_at(canvas, '*', mg_point_make(1, 5));
    assert(result == -1);

    mg_canvas_free(canvas);
}


int
main(int argc, char *argv[])
{
    test_alloc();
    test_set_char_at();
    return EXIT_SUCCESS;
}

