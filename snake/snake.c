#include <play.h>
#include <utility.h>

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <textmode.h>
#include <stdbool.h>
#include <time.h>

// TODO: snake movement operation/algorithm
// TODO: plan apple eating logic
// Plan: (take stock of everything)
// when snake head x, y == apple x, y:
// - snake len ++
// - new apple i.e. change apple location (random)
// TODO: snake death
// Plan:
// -

#define CONSOLE_W 20
#define CONSOLE_H 20
#define CONSOLE_SIZE (CONSOLE_W * CONSOLE_H)

#define MIN_X 0
#define MIN_Y 0

#define TRUE 1
#define FALSE 0

#define FPS 30
#define SECONDS(x) (int)((float)(x) * (float)FPS)
#define UPDATE_INTERVAL_TICKS 15 // how often (interval) does game update
#define SNAKE_INITIAL_LENGTH 4 

// example: probably better than a macro
int SecondsToTicks(float seconds)
{
    return seconds * (float)FPS;
}

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int x;
    int y;
    int ch;
    int fc;
    int bc;
    bool active;
} Entity;

// snake data structure
#define SNAKE_MAX_LEN CONSOLE_SIZE
int dx, dy;
Point snake[SNAKE_MAX_LEN];

int snake_body = SNAKE_INITIAL_LENGTH;  

int main()
{
    //init console
    if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) {
        fprintf(stderr, "Error: SDL_Init() failed! (%s)\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    DOS_InitScreen("Bounder", CONSOLE_W, CONSOLE_H, DOS_MODE40, 4);
    DOS_SetScreenScale(3);
    DOS_SetCursorType(DOS_CURSOR_NONE);
    
    //===================================================
    
    // initial snake
    char snake_ch = 0xB1;
    int snake_cl = DOS_GREEN;

    for ( int i = 0; i < SNAKE_MAX_LEN; i++ ) {
        snake[i].x = CONSOLE_W / 2;
        snake[i].y = CONSOLE_H / 2;
    }
    //init apple
    srand((unsigned)time(NULL));
    
    Entity apple = {
        .x = rand() % CONSOLE_W,
        .y = rand() % CONSOLE_H,
        .ch = 0x95,
        .fc = DOS_RED,
        .bc = 0,
        .active = true,
    };

    DOS_GotoXY(apple.x, apple.y);
    DOS_SetForeground(apple.fc);
    DOS_PrintChar(apple.ch);  

    //===================================================

    // program loop:
    dx = dy = 0;
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
                    if ( event.key.keysym.sym == SDLK_ESCAPE ) {
                        running = false;
                    }
                    if ( event.key.keysym.sym == SDLK_UP ) {
                        dx = 0;
                        dy = -1;
                    }
                    else if ( event.key.keysym.sym == SDLK_LEFT ) {
                        dx = -1;
                        dy = 0;
                    }
                    else if ( event.key.keysym.sym == SDLK_RIGHT ) {
                        dx = +1;
                        dy = 0;
                    }
                    else if ( event.key.keysym.sym == SDLK_DOWN ) {
                        dx = 0;
                        dy = +1;
                    }
                    break;
                default:
                    break;
            }
        }

        // clamp-like code where snake bounces off the walls.
        if ( snake[0].x == MIN_X || snake[0].x == CONSOLE_W - 1 ) {
            dx = -dx;
        }
        if ( snake[0].y == MIN_Y || snake[0].y == CONSOLE_H - 1 ) {
            dy = -dy;
        }
        //===============================================

        // 2) SIMULATE/UPDATE GAME
        //printf("%d\n", snake_body); //debug

        if ( apple.x == snake[0].x && apple.y == snake[0].y ) {
            apple.active = false;

        } else if ( !apple.active ) {
            apple.x = rand() % CONSOLE_W;
            apple.y = rand() % CONSOLE_H;
            
            DOS_GotoXY(apple.x, apple.y);
            DOS_SetForeground(apple.fc);
            DOS_PrintChar(apple.ch);  
            
            apple.active = true;
            snake_body++;        
        }

      
        if ( ticks % SECONDS(0.3f) == 0 ) {
            // temp: dx dy affects head of snake
            snake[0].x += dx;
            snake[0].y += dy;
            
            for ( int i = SNAKE_MAX_LEN; i > 0; i-- ) {
                snake[i].x = snake[i-1].x;
                snake[i].y = snake[i-1].y;
            } 
        }

        //===============================================
           
        // 3) RENDER GAME
        DOS_ClearScreen();
        
        // draw snake
        
        for ( int i = 0; i < snake_body; i++ ) {
            DOS_GotoXY(snake[i].x, snake[i].y);
            DOS_SetForeground(snake_cl);
            DOS_PrintChar(snake_ch);
        }            
            
        // TEMP: draw apple

        if ( apple.active ) {
            DOS_GotoXY(apple.x, apple.y);
            DOS_SetForeground(apple.fc);
            DOS_PrintChar(apple.ch);  
        }
        
        DOS_DrawScreen();
    }
    
    // exit program:
    
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
