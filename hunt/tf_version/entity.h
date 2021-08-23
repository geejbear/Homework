#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>

typedef struct
{
    int     x;
    int     y;
    int     ch;
    int     fg_color;
    int     bg_color;
    bool    active;
} entity_t;

entity_t new_entity(int x, int y, int ch, int fg, int bg);
void draw_entity(entity_t * e);
bool entities_overlap(entity_t * e1, entity_t * e2);

#endif /* ENTITY_H */
