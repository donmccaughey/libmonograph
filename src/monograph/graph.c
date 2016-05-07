#include "graph.h"

#include <stdlib.h>

#include "box.h"


struct mg_graph *
mg_graph_alloc(void)
{
    struct mg_graph *graph = calloc(1, sizeof(struct mg_graph));
    if (!graph) return NULL;
    
    graph->boxes = calloc(1, sizeof(struct mg_box *));
    if (!graph->boxes) {
        mg_graph_free(graph);
        return NULL;
    }

    return graph;
}


void
mg_graph_free(struct mg_graph *graph)
{
    if (!graph) return;
    for (int i = 0; i < graph->boxes_count; ++i) {
        mg_box_free(graph->boxes[i]);
    }
    free(graph->boxes);
    free(graph);
}


int
mg_graph_add(struct mg_graph *graph, struct mg_box *box)
{
    int new_index = graph->boxes_count;
    int new_count = graph->boxes_count + 1;
    size_t new_size = new_count * sizeof(struct mg_box *);
    struct mg_box **new_boxes = realloc(graph->boxes, new_size);
    if (!new_boxes) return -1;
    new_boxes[new_index] = box;
    graph->boxes = new_boxes;
    graph->boxes_count = new_count;
    return 0;
}


void
mg_graph_draw(struct mg_graph const *graph, struct mg_canvas *canvas)
{
    for (int i = 0; i < graph->boxes_count; ++i) {
        mg_box_draw(graph->boxes[i], canvas);
    }
}

