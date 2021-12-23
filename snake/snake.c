#include "snake.h"

#include <textmode.h>

Entity NewEntity(Entity *e, int x, int y, int dx, int dy, char ch, int color) 
{
    e->x = x;
    e->y = y;
    e->dx = dx;
    e->dy = dy;
    e->ch = ch;
    e->fc = color;

    return *e;
}

Entity NewArrayEntity(int array_adress, int array_len, int x, int y, int dx, int dy, char ch, int color) 
{
    Entity array[array_adress];
    
    array[array_adress].x = x;
    array[array_adress].y = y;
    array[array_adress].dx = dx;
    array[array_adress].dy = dy;
    array[array_adress].ch = ch;
    array[array_adress].fc = color;
    

    return array[array_adress];
}

void RenderEntity(Entity *e) 
{
    DOS_GotoXY(e->x, e->y);
    DOS_SetForeground(e->fc);
    DOS_PrintChar(e->ch);
}

void RenderArrayEntity(Entity array[0], int array_adress, int array_len) 
{
    
    DOS_GotoXY(array[array_adress].x, array[array_adress].y);
    DOS_SetForeground(array[array_adress].fc);
    DOS_PrintChar(array[array_adress].ch);        
}

void CollectAppleSoundEffect(void)
{
    DOS_InitSound();
    DOS_Sound(880, 70);        
    DOS_Sound(1720, 70);
}

void WarpToOppositeEnd(int *x, int *y, int max_x, int max_y, int min_x, int min_y)
{   
    if ( *x == max_x ) {
        *x = min_x + 1;
    }
    if ( *y == max_x ) {
        *y = min_y + 1;
    }
    if ( *x == min_x ) {
        *x = max_x - 1;
    }
    if ( *y == min_y ) {
        *y = max_y - 1;
    }
}
