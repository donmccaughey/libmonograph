#include "box.h"

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
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


char *
mg_box_alloc_string(struct mg_box const *box, int *length)
{
    char *rect_string = mg_rect_alloc_string(&box->rect, NULL);
    if (!rect_string) return NULL;
    char *s;
    int chars_printed = asprintf(&s, "box %s %s\n", rect_string, box->title);
    free(rect_string);
    if (length) *length = chars_printed;
    return s;
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


struct mg_box *
mg_box_alloc_from_string(char const *s, int *length)
{
    assert(s);
    if (!s) {
        errno = EINVAL;
        return -1;
    }

    int prefix_length = 0;
    int count = sscanf(s, " box%n", &prefix_length);
    if (count != 0) return NULL;
    s += prefix_length;

    struct mg_box *box = calloc(1, sizeof(struct mg_box));
    if (!box) return NULL;
    
    int rect_length = 0;
    int result = mg_rect_from_string(s, &box->rect, &rect_length);
    if (result == -1) {
        mg_box_free(box);
        return NULL;
    }
    s += rect_length;

    int leading_space_length = 0;
    count = sscanf(s, " %n", &leading_space_length);
    if (count != 0) {
        mg_box_free(box);
        return NULL;
    }
    s += leading_space_length;

    char *title_start = s;
    size_t length_to_end = strcspn(title_start, "\n");
    size_t title_length = length_to_end;
    int newline_length = title_start[title_length] ? 1 : 0;

    while (isspace(title_start[title_length - 1])) --title_length; 
    box->title = strndup(title_start, title_length);
    if (!box->title) {
        mg_box_free(box);
        return NULL;
    }

    if (length) *length = prefix_length + rect_length
        + leading_space_length + length_to_end + newline_length;
    return box;
}

