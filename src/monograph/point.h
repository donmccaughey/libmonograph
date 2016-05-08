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

char *
mg_point_alloc_string(struct mg_point point, int *length);

int
mg_point_from_string(char const *s, struct mg_point *point, int *length);


#endif

