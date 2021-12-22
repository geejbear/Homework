#ifndef SNAKE_H
#define SNAKE_H

typedef struct 
{
    int x;
    int y;
    int dx;
    int dy;
    char ch;
    int fc;
}Entity;

Entity NewEntity(Entity *e, int x, int y, int dx, int dy, char ch, int color); 
Entity NewArrayEntity(int array_adress, int array_len, int x, int y, int dx, int dy, char ch, int color); 
void RenderEntity(Entity *e); 
void RenderArrayEntity(Entity array[0], int array_adress, int array_len); 
void CollectAppleSoundEffect(void);
void WarpToOppositeEnd(int *x, int *y, int max_x, int max_y, int min_x, int min_y);

#endif
