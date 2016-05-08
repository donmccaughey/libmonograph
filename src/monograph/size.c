#include "size.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>


extern inline struct mg_size
mg_size_make(int width, int height);


char *
mg_size_alloc_string(struct mg_size size, int *length)
{
    char *s;
    int chars_printed = asprintf(&s, "%dx%d", size.width, size.height);
    if (length) *length = chars_printed;
    return s;
}


int
mg_size_from_string(char const *s, struct mg_size *size, int *length)
{
    assert(s);
    assert(size);
    if (!s || !size) {
        errno = EINVAL;
        return -1;
    }
    int chars_scanned = 0;
    int count = sscanf(s, " %d x %d%n", &size->width, &size->height, &chars_scanned);
    if (count != 2) return -1;
    if (length) *length = chars_scanned;
    return 0;
}

