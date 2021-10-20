#include <play.h>
#include <utility.h>

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <textmode.h>
#include <stdbool.h>
#include <time.h>

#define CONSOLE_W 20
#define CONSOLE_H 20
#define CONSOLE_SIZE (CONSOLE_W * CONSOLE_H)
#define TRUE 1
#define FALSE 0
#define MAX_SNAKE_ARRAY 100
#define GAME_SPEED 30
#define TICK_CYCLE 15
#define SNAKE_BODY 3

//Bugs:
// Redifine input to avoid syncopation when the snake is turned

typedef struct
{
    int x, y;
    int dx, dy;
    int ch;
    int color;
    bool active; 
} Entity;

Entity snake = {
    .x = CONSOLE_W / 2,
    .y = CONSOLE_H / 2,
    .dx = 0,
    .dy = -1,
    .ch = DOS_SQUARE,
    .color = DOS_GRAY,
    .active = true,
};

Entity apple = {
    .x = CONSOLE_W / 4,
    .y = CONSOLE_H / 4,
    .dx = 0,
    .dy = 0,
    .ch = DOS_DOT1,
    .color = DOS_RED,
    .active = true,
};

int main()
{
    if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) {
        fprintf(stderr, "Error: SDL_Init() failed! (%s)\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    DOS_InitScreen("Bounder", CONSOLE_W, CONSOLE_H, DOS_MODE40, 4);
    DOS_SetScreenScale(3);
    DOS_SetCursorType(DOS_CURSOR_NONE);
    
    int player_x = CONSOLE_W / 2;
    int player_y = CONSOLE_H / 2;

    int apple_x = CONSOLE_W / 4;
    int apple_y = CONSOLE_H / 4;
        

    // program loop:

    int ticks = 0;
    bool running = true;
    while ( running ) {
        DOS_LimitFrameRate(GAME_SPEED);
        
        // 1) GET INPUT
        SDL_Event event;
        while ( SDL_PollEvent(&event) ) {
            switch ( event.type ) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    if ( event.key.keysym.sym == SDLK_UP ) {
                        snake.y--; //rather turn head 90 degrees
                    }
                    if ( event.key.keysym.sym == SDLK_LEFT  ) {
                        snake.x--;
                    }
                    if ( event.key.keysym.sym == SDLK_RIGHT ) {
                        snake.x++;
                    }
                    if ( event.key.keysym.sym == SDLK_DOWN ) {
                        snake.y++;
                    }

                default:
                    break;
            }
        }

        // 2) SIMULATE/UPDATE GAME
        
        if (ticks % TICK_CYCLE == 0 && event.key.keysym.sym == SDLK_UP) {
            snake.x += snake.dx;
            snake.y += snake.dy;
        }   

        if ( ticks % TICK_CYCLE == 0 && event.key.keysym.sym == SDLK_LEFT  ) {
            snake.x += -1;
            snake.y += 0;
        }
        if ( ticks % TICK_CYCLE == 0 && event.key.keysym.sym == SDLK_RIGHT ) {
            snake.x += +1;
            snake.y += 0;
        }
        if ( ticks % TICK_CYCLE == 0 && event.key.keysym.sym == SDLK_DOWN ) {
            snake.x += 0;
            snake.y += +1;
        } 
        ticks++;
        //Ask Tom about printf ticks 
      
        // 3) RENDER GAME
        DOS_ClearScreen();
        
        
        // draw player
        int segs[SNAKE_BODY];
        DOS_GotoXY(snake.x, snake.y);
        DOS_PrintChar(snake.ch);
        
        
        // draw apple
    
        DOS_GotoXY(apple.x, apple.y);
        DOS_SetForeground(apple.color);
        DOS_PrintChar(apple.ch);  
        

        DOS_DrawScreen();
    }
    
    // exit program:
    
    SDL_Quit();
    
    return EXIT_SUCCESS;
}