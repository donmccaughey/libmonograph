#include "canvas.h"

#include <stdlib.h>
#include <string.h>


static int
get_text_length(struct mg_size size)
{
    return (size.width + 1) * size.height;
}


struct mg_canvas *
mg_canvas_alloc(struct mg_size size)
{
    struct mg_canvas *canvas = calloc(1, sizeof(struct mg_canvas));
    if (!canvas) return NULL;

    canvas->size = size;

    size_t text_size = get_text_length(size) + 1;
    canvas->text = malloc(text_size);
    if (!canvas->text) {
        mg_canvas_free(canvas);
        return NULL;
    }
    mg_canvas_clear(canvas);

    return canvas;
}


void
mg_canvas_clear(struct mg_canvas *canvas)
{
    char *line = canvas->text;
    for (int i = 0; i < canvas->size.height; ++i) {
        memset(line, ' ', canvas->size.width);
        line += canvas->size.width;
        *line = '\n';
        ++line;
    }
    *line = '\0';
}


void
mg_canvas_free(struct mg_canvas *canvas)
{
    if (!canvas) return;
    free(canvas->text);
    free(canvas);
}

int
mg_canvas_get_text_length(struct mg_canvas const *canvas)
{
    return get_text_length(canvas->size); 
}


int
mg_canvas_set_char_at(struct mg_canvas *canvas, char ch, struct mg_point point)
{
    if (point.x < 0) return -1;
    if (point.y < 0) return -1;
    if (point.x >= canvas->size.width) return -1;
    if (point.y >= canvas->size.height) return -1;
    int index = (point.y * (canvas->size.width + 1)) + point.x;
    canvas->text[index] = ch;
    return 0;
}

