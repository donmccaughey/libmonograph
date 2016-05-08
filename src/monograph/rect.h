#ifndef MONOGRAPH_RECT_H_INCLUDED
#define MONOGRAPH_RECT_H_INCLUDED

#include <stdbool.h>

#include <monograph/point.h>
#include <monograph/size.h>


struct mg_rect {
    struct mg_point point;
    struct mg_size size;
};


inline struct mg_rect
mg_rect_make(struct mg_point point, struct mg_size size)
{
    return (struct mg_rect){ .point=point, .size=size };
}

char *
mg_rect_alloc_string(struct mg_rect const *rect, int *length);

int
mg_rect_from_string(char const *s, struct mg_rect *rect, int *length);


#endif

