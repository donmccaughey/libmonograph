#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <monograph/monograph.h>


static void
test_alloc(void)
{
    struct mg_graph *graph = mg_graph_alloc();

    assert(graph);
    assert(graph->boxes);
    assert(graph->boxes_count == 0);

    mg_graph_free(graph);
}


static void
test_add(void)
{
    struct mg_graph *graph = mg_graph_alloc();
    
    assert(graph->boxes_count == 0);

    struct mg_rect rect = mg_rect_make(mg_point_make(0, 0), mg_size_make(3, 7));
    struct mg_box *box = mg_box_alloc(&rect, "box 1");
    int result = mg_graph_add(graph, box);

    assert(result == 0);
    assert(graph->boxes_count == 1);
    assert(graph->boxes[0] == box);
    
    rect = mg_rect_make(mg_point_make(1, 4), mg_size_make(3, 7));
    box = mg_box_alloc(&rect, "box 2");
    result = mg_graph_add(graph, box);

    assert(result == 0);
    assert(graph->boxes_count == 2);
    assert(graph->boxes[1] == box);

    mg_graph_free(graph);
}


static void
test_draw(void)
{
    struct mg_graph *graph = mg_graph_alloc();
    struct mg_rect rect = mg_rect_make(mg_point_make(0, 0), mg_size_make(7, 3));
    struct mg_box *box = mg_box_alloc(&rect, "box 1");
    mg_graph_add(graph, box);

    rect = mg_rect_make(mg_point_make(1, 4), mg_size_make(7, 3));
    box = mg_box_alloc(&rect, "box 2");
    mg_graph_add(graph, box);

    struct mg_canvas *canvas = mg_canvas_alloc(mg_size_make(10, 8));
    mg_graph_draw(graph, canvas);
    
    char const expected_text[] = 
        "+-----+   \n"
        "|box 1|   \n"
        "+-----+   \n"
        "          \n"
        " +-----+  \n"
        " |box 2|  \n"
        " +-----+  \n"
        "          \n"
        ;
    assert(strcmp(canvas->text, expected_text) == 0);

    mg_canvas_free(canvas);
    mg_graph_free(graph);
}


int
main(int argc, char *argv[])
{
    test_alloc();
    test_add();
    test_draw();
    return EXIT_SUCCESS;
}

