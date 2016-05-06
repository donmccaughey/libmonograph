#ifndef MONOGRAPH_RECT_H_INCLUDED
#define MONOGRAPH_RECT_H_INCLUDED


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


#endif

