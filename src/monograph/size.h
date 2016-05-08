#ifndef MONOGRAPH_SIZE_H_INCLUDED
#define MONOGRAPH_SIZE_H_INCLUDED


struct mg_size {
    int width, height;
};


inline struct mg_size
mg_size_make(int width, int height)
{
    return (struct mg_size){ .width=width, .height=height };
}

char *
mg_size_alloc_string(struct mg_size size, int *length);

int
mg_size_from_string(char const *s, struct mg_size *size, int *length);

 
#endif

