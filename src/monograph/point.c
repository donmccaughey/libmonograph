#include "point.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>


extern inline struct mg_point
mg_point_make(int x, int y);


char *
mg_point_alloc_string(struct mg_point point, int *length)
{
    char *s;
    int chars_printed = asprintf(&s, "(%d, %d)", point.x, point.y);
    if (length) *length = chars_printed;
    return s;
}


int
mg_point_from_string(char const *s, struct mg_point *point, int *length)
{
    assert(s);
    assert(point);
    if (!s || !point) {
        errno = EINVAL;
        return -1;
    }
    int chars_scanned = 0;
    int count = sscanf(s, " ( %d , %d )%n", &point->x, &point->y, &chars_scanned);
    if (count != 2) return -1;
    if (length) *length = chars_scanned;
    return 0;
}

