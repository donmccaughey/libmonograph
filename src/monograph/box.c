#include "box.h"

#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "canvas.h"


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
mg_box_draw(struct mg_box const *box, struct mg_canvas *canvas)
{
    int left_border_width = 1;
    int right_border_width = 1;
    int interior_width = box->rect.size.width - left_border_width - right_border_width;

    int top_border_height = 1;
    int bottom_border_height = 1;
    int interior_height = box->rect.size.height - top_border_height - bottom_border_height;

    size_t full_title_length = strlen(box->title);
    assert(full_title_length <= INT_MAX);

    int title_length = (int)full_title_length < interior_width
        ? (int)full_title_length : interior_width;
    int title_x = box->rect.point.x + left_border_width
        + ((interior_width - (int)title_length) / 2);
    int title_max_x = title_x + title_length - 1;

    int title_height = interior_height ? 1 : 0;
    int title_y = box->rect.point.y + top_border_height
        + ((interior_height - title_height) / 2);
    int title_max_y = title_y + title_height - 1;

    int max_i = box->rect.size.width - 1;
    int max_j = box->rect.size.height - 1;
    for (int j = 0; j <= max_j; ++j) {
        int y = box->rect.point.y + j;
        if (y < 0) continue;
        if (y > canvas->size.height) continue;
        for (int i = 0; i <= max_i; ++i) {
            int x = box->rect.point.x + i;
            if (x < 0) continue;
            if (x > canvas->size.width) continue;
            char ch = ' ';
            if (i == 0 && j == 0) {
                ch = '+';
            } else if (i == max_i && j == 0) {
                ch = '+';
            } else if (i == 0 && j == max_j) {
                ch = '+';
            } else if (i == max_i && j == max_j) {
                ch = '+';
            } else if (i == 0) {
                ch = '|';
            } else if (i == max_i) {
                ch = '|';
            } else if (j == 0) {
                ch = '-';
            } else if (j == max_j) {
                ch = '-';
            } else if (y >= title_y && x >= title_x && y <= title_max_y && x <= title_max_x) {
                int index = x - title_x;
                ch = box->title[index];
            } 
            struct mg_point point = mg_point_make(x, y);
            mg_canvas_set_char_at(canvas, ch, point);
        }
    }
}


void
mg_box_free(struct mg_box *box)
{
    if (!box) return;
    free(box->title);
    free(box);
}

