#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <monograph/monograph.h>

#include "config.h"


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
    struct mg_box *box = mg_box_alloc(&rect, "title 1");
    int result = mg_graph_add(graph, box);

    assert(result == 0);
    assert(graph->boxes_count == 1);
    assert(graph->boxes[0] == box);
    
    rect = mg_rect_make(mg_point_make(1, 4), mg_size_make(3, 7));
    box = mg_box_alloc(&rect, "title 2");
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
    struct mg_rect rect = mg_rect_make(mg_point_make(0, 0), mg_size_make(9, 3));
    struct mg_box *box = mg_box_alloc(&rect, "title 1");
    mg_graph_add(graph, box);

    rect = mg_rect_make(mg_point_make(1, 4), mg_size_make(9, 3));
    box = mg_box_alloc(&rect, "title 2");
    mg_graph_add(graph, box);

    struct mg_canvas *canvas = mg_canvas_alloc(mg_size_make(10, 8));
    mg_graph_draw(graph, canvas);
    
    char const expected_text[] = 
        "+-------+ \n"
        "|title 1| \n"
        "+-------+ \n"
        "          \n"
        " +-------+\n"
        " |title 2|\n"
        " +-------+\n"
        "          \n"
        ;
    assert(strcmp(canvas->text, expected_text) == 0);

    mg_canvas_free(canvas);
    mg_graph_free(graph);
}


static void
test_alloc_string(void)
{
    struct mg_graph *graph = mg_graph_alloc();
    struct mg_rect rect = mg_rect_make(mg_point_make(1, 2), mg_size_make(9, 3));
    struct mg_box *box = mg_box_alloc(&rect, "title 1");
    mg_graph_add(graph, box);

    rect = mg_rect_make(mg_point_make(3, 4), mg_size_make(11, 4));
    box = mg_box_alloc(&rect, "title 2");
    mg_graph_add(graph, box);

    int length = 0;
    char *s = mg_graph_alloc_string(graph, &length);
    assert(s);
    char const expected_s[] =
        "monograph 0.1\n"
        "box (1, 2) 9x3 title 1\n"
        "box (3, 4) 11x4 title 2\n"
        ;
    assert(strcmp(s, expected_s) == 0);
    assert(length == 61);

    free(s);
    mg_graph_free(graph);
}


static void
test_alloc_from_string(void)
{
    char const s[] = 
        " monograph\t 0.1 \n"
        "  box (1,2)9x3 title 1 \n"
        "box( 3 , 4 ) 11 x 4 title 2\n"
        " "
        ;
    int length = 0;
    struct mg_graph *graph = mg_graph_alloc_from_string(s, &length);
    assert(graph);
    assert(graph->boxes_count == 2);
    
    assert(graph->boxes[0]->rect.point.x == 1);
    assert(graph->boxes[0]->rect.point.y == 2);
    assert(graph->boxes[0]->rect.size.width == 9);
    assert(graph->boxes[0]->rect.size.height == 3);
    assert(strcmp(graph->boxes[0]->title, "title 1") == 0);

    assert(graph->boxes[1]->rect.point.x == 3);
    assert(graph->boxes[1]->rect.point.y == 4);
    assert(graph->boxes[1]->rect.size.width == 11);
    assert(graph->boxes[1]->rect.size.height == 4);
    assert(strcmp(graph->boxes[1]->title, "title 2") == 0);
    
    mg_graph_free(graph);
}


static void
test_alloc_from_file(void)
{
    char const path[] = TEST_DATA_DIR "/test1.monograph";
    struct mg_graph *graph = mg_graph_alloc_from_file(path);
    assert(graph);
    assert(graph->boxes_count == 3);

    assert(graph->boxes[0]->rect.point.x == 4);
    assert(strcmp(graph->boxes[0]->title, "title 1") == 0);

    assert(graph->boxes[1]->rect.point.x == 8);
    assert(strcmp(graph->boxes[1]->title, "title 2") == 0);

    assert(graph->boxes[2]->rect.point.x == 12);
    assert(strcmp(graph->boxes[2]->title, "title 3") == 0);

    mg_graph_free(graph);
}


static void
test_write_file(void)
{
    char const s[] = 
        "monograph 0.1\n"
        "box (0, 0) 9x3 title 1\n"
        "box (4, 4) 11x5 title 2\n"
        ;
    struct mg_graph *graph = mg_graph_alloc_from_string(s, NULL);
    assert(graph);

    char const path[] = "test_write_file.monograph";
    int result = mg_graph_write_file(graph, path);
    assert(result != -1);

    free(graph);

    char buffer[80];
    FILE *f = fopen(path, "r");
    assert(f);

    char *line = fgets(buffer, sizeof buffer, f);
    assert(strcmp(line, "monograph 0.1\n") == 0);
    
    line = fgets(buffer, sizeof buffer, f);
    assert(strcmp(line, "box (0, 0) 9x3 title 1\n") == 0);
    
    line = fgets(buffer, sizeof buffer, f);
    assert(strcmp(line, "box (4, 4) 11x5 title 2\n") == 0);
    
    line = fgets(buffer, sizeof buffer, f);
    assert(line == NULL);

    fclose(f);
    unlink(path);
}


int
main(int argc, char *argv[])
{
    test_alloc();
    test_add();
    test_draw();
    test_alloc_string();
    test_alloc_from_string();
    test_alloc_from_file();
    test_write_file();
    return EXIT_SUCCESS;
}

