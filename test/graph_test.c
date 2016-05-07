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


int
main(int argc, char *argv[])
{
    test_alloc();
    return EXIT_SUCCESS;
}

