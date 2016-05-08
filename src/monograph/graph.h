#ifndef MONOGRAPH_GRAPH_H_INCLUDED
#define MONOGRAPH_GRAPH_H_INCLUDED


struct mg_box;
struct mg_canvas;


struct mg_graph {
    struct mg_box **boxes;
    int boxes_count;
};


struct mg_graph *
mg_graph_alloc(void);

void
mg_graph_free(struct mg_graph *graph);

int
mg_graph_add(struct mg_graph *graph, struct mg_box *box);

void
mg_graph_draw(struct mg_graph const *graph, struct mg_canvas *canvas);

char *
mg_graph_alloc_string(struct mg_graph const *graph, int *length);

struct mg_graph *
mg_graph_alloc_from_string(char const *s, int *length);


#endif

