#include "entity.h"

#include <conio.h>

entity_t new_entity(int x, int y, int ch, int fg, int bg)
{
    entity_t new;
    
    new.x = x;
    new.y = y;
    new.ch = ch;
    new.fg_color = fg;
    new.bg_color = bg;
    new.active = true;
    
    return new;
}


void draw_entity(entity_t * e)
{
    if ( e->active ) {
        textcolor(e->fg_color);
        textbackground(e->bg_color);
        gotoxy(e->x, e->y);
        putch(e->ch);
    }
}


bool entities_overlap(entity_t * e1, entity_t * e2)
{
    return e1->x == e2->x && e1->y == e2->y;
}
