#include <utility.h>

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <textmode.h>
#include <stdbool.h>


#define CONSOLE_H 15
#define CONSOLE_W 15
#define MIN_X 0
#define MIN_Y 0
#define FPS 30
#define SNAKE_ARRAY_SIZE 100

typedef struct 
{
    int x;
    int y;
    int dx;
    int dy;
    char ch;
    int fc;
    bool active;
}Entity;

Entity NewEntity(Entity *e, int x, int y, int dx, int dy, char ch, int color) 
{
    e->x = x;
    e->y = y;
    e->dx = dx;
    e->dy = dy;
    e->ch = ch;
    e->fc = color;
    e->active = true;

    return *e;
}

void RenderEntity(Entity *e) 
{
    if ( e->active ) {
        DOS_GotoXY(e->x, e->y);
        DOS_SetForeground(e->fc);
        DOS_PrintChar(e->ch);
    }
}

void RenderArrayEntity(Entity *e, int value) 
{
    if ( e->active ) {
        for ( int i = 0; i < value; i++ ) {
            DOS_GotoXY(e->x, e->y);
            DOS_SetForeground(e->fc);
            DOS_PrintChar(e->ch);
        }
    }
}

int IsSDLInit() 
{
    if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) {
        fprintf(stderr, "Error: SDL_Init() failed! (%s)\n", SDL_GetError());
    }
    return EXIT_FAILURE;
}

void InitScreen()
{
    DOS_InitScreen("Bounder", CONSOLE_W, CONSOLE_H, DOS_MODE40, 4);
    DOS_SetScreenScale(3);
    DOS_SetCursorType(DOS_CURSOR_NONE);
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


int main()
{
    //init console
    IsSDLInit();
    InitScreen();
    
    srand((unsigned)time(NULL));
    int snake_len = 4;
    
    Entity snake[SNAKE_ARRAY_SIZE];
    NewEntity(&snake[snake_len], CONSOLE_W / 2, CONSOLE_H / 2, 0, 0, 0xB1, DOS_GREEN);
    
    
    Entity apple;
    NewEntity(&apple, rand() % CONSOLE_H, rand() % CONSOLE_W, 0, 0, 0x95, DOS_RED);
    
    
    bool running = true;
    int ticks = 0;
    while ( running ) {
        ticks++;

        DOS_LimitFrameRate(FPS);
         // 1) GET INPUT
        SDL_Event event;
        while ( SDL_PollEvent(&event) ) {
            switch ( event.type ) {
                case SDL_QUIT:
                    running = false;
                    break;  
                case SDL_KEYDOWN:
                    //Input(SDL_KEYDOWN, running, event);
                    if ( event.key.keysym.sym == SDLK_ESCAPE ) {
                        running = false;
                    }
                    if ( event.key.keysym.sym == SDLK_UP ) {
                        snake[snake_len].dx = 0;
                        snake[snake_len].dy = -1;
                    }
                    else if ( event.key.keysym.sym == SDLK_LEFT ) {
                        snake[snake_len].dx = -1;
                        snake[snake_len].dy = 0;
                    }
                    else if ( event.key.keysym.sym == SDLK_RIGHT ) {
                        snake[snake_len].dx = +1;
                        snake[snake_len].dy = 0;
                    }
                    else if ( event.key.keysym.sym == SDLK_DOWN ) {
                        snake[snake_len].dx = 0;
                        snake[snake_len].dy = +1;
                    }
                    break;
                default:
                    break;
            }
        }    
       //Update game

        if ( ticks % 10 == 0 ) {
            snake[snake_len].x += snake[snake_len].dx;
            snake[snake_len].y += snake[snake_len].dy;
        }
        
        if ( apple.x == snake[snake_len].x && apple.y == snake[snake_len].y ) {
            CollectAppleSoundEffect();
            apple.x = rand() % CONSOLE_W;
            apple.y = rand() % CONSOLE_H; 

        }  

        WarpToOppositeEnd(&snake[snake_len].x, &snake[snake_len].y, CONSOLE_W, CONSOLE_H, MIN_X, MIN_Y);
      
        //Draw game
        DOS_ClearScreen();
       
        RenderArrayEntity(&snake[snake_len], snake_len);
        
        RenderEntity(&apple);

        DOS_DrawScreen();
    }    
    
    SDL_Quit();
    
    return EXIT_SUCCESS;
}