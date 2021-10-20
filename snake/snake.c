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
#define FPS 30
#define SECONDS(x) (int)((float)(x) * (float)FPS)
#define UPDATE_INTERVAL_TICKS 15 // how often (interval) does game update
#define SNAKE_BODY 3 // SNAKE_INITIAL_LENGTH 3

//Bugs:
// Redifine input to avoid syncopation when the snake is turned

// example: probably better than a macro
int SecondsToTicks(float seconds)
{
    return seconds * (float)FPS;
}

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
    .dy = -1, // TF: start at 0
    //.ch = DOS_SQUARE,
    .ch = 'S',
    .color = DOS_GRAY,
    .active = true,
};

Entity apple = {
    .x = CONSOLE_W / 4,
    .y = CONSOLE_H / 4,
    .dx = 0,
    .dy = 0,
    //.ch = DOS_DOT1,
    .ch = 'A',
    .color = DOS_RED,
    .active = true,
};

typedef struct {
    int x;
    int y;
} Point;

// snake data structure
#define SNAKE_MAX_LEN CONSOLE_SIZE
int dx, dy;
Point _snake[SNAKE_MAX_LEN];
int snake_len = SNAKE_BODY;

int main()
{
    if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) {
        fprintf(stderr, "Error: SDL_Init() failed! (%s)\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    DOS_InitScreen("Bounder", CONSOLE_W, CONSOLE_H, DOS_MODE40, 4);
    DOS_SetScreenScale(3);
    DOS_SetCursorType(DOS_CURSOR_NONE);
    
    // initial snake
    dx = dy = 0;
    for ( int i = 0; i < snake_len; i++ ) {
        _snake[i].x = CONSOLE_W / 2;
        _snake[i].y = CONSOLE_H / 2;
    }
    
    
    // program loop:

    int ticks = 0;
    bool running = true;
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
                    // TODO: switch
                    if ( event.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                    }
                    
                    if ( event.key.keysym.sym == SDLK_UP ) {
                        snake.dy = -1;
                        snake.dx = 0;
                    }
                    else if ( event.key.keysym.sym == SDLK_LEFT  ) {
                        snake.dx = -1;
                        snake.dy = 0;
                    }
                    else if ( event.key.keysym.sym == SDLK_RIGHT ) {
                        snake.dx = +1;
                        snake.dy = 0;
                    }
                    else if ( event.key.keysym.sym == SDLK_DOWN ) {
                        snake.dy = +1;
                        snake.dx = 0;
                    }
                    break;
                default:
                    break;
            }
        }

        // 2) SIMULATE/UPDATE GAME
        
        if (ticks % SECONDS(0.5f) == 0) {
            snake.x += snake.dx;
            snake.y += snake.dy;

            // temp: dx dy affects head of snake
            _snake[0].x += dx;
            _snake[0].y += dy;
//            for ( int segment_index = ?; segment_index ?; segment_index ?) {
                
//            }
        }
        
        //Ask Tom about printf ticks 
      
        // 3) RENDER GAME
        DOS_ClearScreen();
        
        
        // draw player
        int segs[SNAKE_BODY];
        DOS_GotoXY(snake.x, snake.y);
//        DOS_PrintChar(snake.ch);
        for ( int i = 0; i < snake_len; i++ ) {
            DOS_GotoXY(_snake[i].x, _snake[i].y);
            DOS_SetForeground(DOS_BLUE);
            DOS_PrintChar(219);
        }
        
        
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
