#ifndef MONOGRAPH_BOX_H_INCLUDED
#define MONOGRAPH_BOX_H_INCLUDED


#include <monograph/rect.h>


struct mg_canvas;


struct mg_box {
    struct mg_rect rect;
    char *title;
};


struct mg_box *
mg_box_alloc(struct mg_rect const *rect, char const *title);

void
mg_box_free(struct mg_box *box);

void
mg_box_draw(struct mg_box const *box, struct mg_canvas *canvas);


#endif

