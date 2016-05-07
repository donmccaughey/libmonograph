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


inline bool
mg_rect_is_top_left(struct mg_rect const *rect, struct mg_point point)
{
    return rect->point.x == point.x
        && rect->point.y == point.y;
}


inline bool
mg_rect_is_top_right(struct mg_rect const *rect, struct mg_point point)
{
    return rect->point.x + rect->size.width - 1 == point.x
        && rect->point.y == point.y;
}


inline bool
mg_rect_is_bottom_left(struct mg_rect const *rect, struct mg_point point)
{
    return rect->point.x == point.x
        && rect->point.y + rect->size.height - 1 == point.y;
}


inline bool
mg_rect_is_bottom_right(struct mg_rect const *rect, struct mg_point point)
{
    return rect->point.x + rect->size.width - 1 == point.x
        && rect->point.y + rect->size.height - 1 == point.y;
}


#endif

