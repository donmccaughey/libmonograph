#ifndef MONOGRAPH_CANVAS_H_INCLUDED
#define MONOGRAPH_CANVAS_H_INCLUDED


#include <monograph/point.h>
#include <monograph/size.h>


struct mg_canvas {
    struct mg_size size;
    char *text;
};


struct mg_canvas *
mg_canvas_alloc(struct mg_size size);

void
mg_canvas_free(struct mg_canvas *canvas);

int
mg_canvas_get_text_length(struct mg_canvas const *canvas);

void
mg_canvas_clear(struct mg_canvas *canvas);

int
mg_canvas_set_char_at(struct mg_canvas *canvas, char ch, struct mg_point point);


#endif

