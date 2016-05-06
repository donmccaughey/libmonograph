#ifndef MONOGRAPH_POINT_H_INCLUDED
#define MONOGRAPH_POINT_H_INCLUDED


struct mg_point {
    int x, y;
};


inline struct mg_point
mg_point_make(int x, int y)
{
    return (struct mg_point){ .x=x, .y=y };
}


#endif

