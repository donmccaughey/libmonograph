#include "rect.h"


extern inline bool
mg_rect_is_bottom_left(struct mg_rect const *rect, struct mg_point point);

extern inline bool
mg_rect_is_bottom_right(struct mg_rect const *rect, struct mg_point point);

extern inline bool
mg_rect_is_top_left(struct mg_rect const *rect, struct mg_point point);

extern inline bool
mg_rect_is_top_right(struct mg_rect const *rect, struct mg_point point);

extern inline struct mg_rect
mg_rect_make(struct mg_point point, struct mg_size size);

