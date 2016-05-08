#include "graph.h"

#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "box.h"
#include "config.h"


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


struct mg_graph *
mg_graph_alloc_from_string(char const *s, int *length)
{
    assert(s);
    if (!s) {
        errno = EINVAL;
        return NULL;
    }

    int prefix_length;
    int major_version;
    int minor_version;
    int count = sscanf(s, " monograph %d . %d%n", 
            &major_version, &minor_version, &prefix_length);
    if (count != 2) return NULL;
    if (major_version != 0) return NULL;
    if (minor_version != 1) return NULL;
    s += prefix_length;

    struct mg_graph *graph = mg_graph_alloc();
    if (!graph) return NULL;

    struct mg_box *box;
    int boxes_length = 0;
    while (true) {
        int box_length;
        box = mg_box_alloc_from_string(s, &box_length);
        if (box) {
            boxes_length += box_length;
            s += box_length;
            int result = mg_graph_add(graph, box);
            if (result == -1) {
                mg_graph_free(graph);
                return NULL;
            }
        } else {
            // TODO: distinguish between error and end of file
            break;
        }
    }

    if (length) *length = prefix_length + boxes_length;
    return graph;
}


char *
mg_graph_alloc_string(struct mg_graph const *graph, int *length)
{
    int header_lines_count = 1;
    int lines_count = header_lines_count + graph->boxes_count;
    char *lines[lines_count];
    int lengths[lines_count];
    
    lines[0] = strdup("monograph " PACKAGE_VERSION "\n");
    if (!lines[0]) return NULL;
    size_t length0 = strlen(lines[0]);
    assert(length0 <= (size_t)INT_MAX);
    if (length0 > (size_t)INT_MAX) {
        errno = ERANGE;
        free(lines[0]);
        return NULL;
    }
    lengths[0] = (int)length0;
    int total_length = lengths[0];

    for (int i = 0; i < graph->boxes_count; ++i) {
        int index = i + 1;
        int length;
        lines[index] = mg_box_alloc_string(graph->boxes[i], &length);
        if (!lines[index]) {
            while (index >= 0) {
                free(lines[index]);
                --index;
            }
            return NULL;
        }
        lengths[index] = length;
        total_length += length;
    }
    
    size_t terminator_size = 1;
    size_t size = (size_t)total_length + terminator_size;
    char *s = malloc(size);
    if (!s) {
        for (int i = 0; i < lines_count; ++i) free(lines[i]);
        return NULL;
    }

    char *s1 = s;
    for (int i = 0; i < lines_count; ++i) {
        strcpy(s1, lines[i]);
        s1 += lengths[i];
    }
    *s1 = '\0';

    return s;
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

