#include "box.h"

#include <stdlib.h>
#include <string.h>


struct mg_box *
mg_box_alloc(struct mg_rect const *rect, char const *title)
{
    struct mg_box *box = calloc(1, sizeof(struct mg_box));
    if (!box) return NULL;
    
    box->rect = *rect;

    box->title = strdup(title);
    if (!box->title) {
        mg_box_free(box);
        return NULL;
    }

    return box;
}


void
mg_box_free(struct mg_box *box)
{
    if (!box) return;
    free(box->title);
    free(box);
}

