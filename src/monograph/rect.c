#include "rect.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>


extern inline struct mg_rect
mg_rect_make(struct mg_point point, struct mg_size size);


char *
mg_rect_alloc_string(struct mg_rect const *rect, int *length)
{
    char *point_string = mg_point_alloc_string(rect->point, NULL);
    if (!point_string) return NULL;
    char *size_string = mg_size_alloc_string(rect->size, NULL);
    if (!size_string) {
        free(point_string);
        return NULL;
    }
    char *s;
    int chars_printed = asprintf(&s, "%s %s", point_string, size_string);
    free(point_string);
    free(size_string);
    if (length) *length = chars_printed;
    return s;
}


int
mg_rect_from_string(char const *s, struct mg_rect *rect, int *length)
{
    assert(s);
    assert(rect);
    if (!s || !rect) {
        errno = EINVAL;
        return -1;
    }
    int point_length = 0;
    int result = mg_point_from_string(s, &rect->point, &point_length);
    if (result == -1) return -1;
    s += point_length;
    int size_length = 0;
    result = mg_size_from_string(s, &rect->size, &size_length);
    if (result == -1) return -1;
    if (length) *length = point_length + size_length;
    return 0;
}

