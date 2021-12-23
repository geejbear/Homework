#include "snake.h"

#include <utility.h>

#include <stdio.h>
#include <stdbool.h>
#include <textmode.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define CONSOLE_H 15
#define CONSOLE_W 15
#define MIN_X 0
#define MIN_Y 0
#define FPS 30
#define SNAKE_ARRAY_LEN 100
#define SNAKE_CHAR 0xB1
#define APPLE_CHAR 0x95

#if 0
void loop_array(Entity *array)
{
    int i = 0;
    while ( i < SNAKE_ARRAY_LEN ) {
        array[i] = 'S';
        i += 1;
    }
}
#endif

int IsSDLInit() 
{
    if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) {
        fprintf(stderr, "Error: SDL_Init() failed! (%s)\n", SDL_GetError());
    }
    return EXIT_FAILURE;
}

void InitScreen()
{
    DOS_InitScreen("snake", CONSOLE_W, CONSOLE_H, DOS_MODE40, 4);
    DOS_SetScreenScale(3);
    DOS_SetCursorType(DOS_CURSOR_NONE);
}

Entity snake[SNAKE_ARRAY_LEN];
Entity apple;

int main()
{
    //init console
    IsSDLInit();
    InitScreen();
    
    srand((unsigned)time(NULL));
    int snake_head = 0;
    int snake_len = 4;
    
    snake[snake_head] = NewArrayEntity(snake_head, snake_len, CONSOLE_W / 2, CONSOLE_H / 2, 0, 0, SNAKE_CHAR, DOS_GREEN); //snake
    
    NewEntity(&apple, rand() % CONSOLE_H, rand() % CONSOLE_W, 0, 0, APPLE_CHAR, DOS_RED); //apple
    
    
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
                        snake[snake_head].dx = 0;
                        snake[snake_head].dy = -1;
                    }
                    else if ( event.key.keysym.sym == SDLK_LEFT ) {
                        snake[snake_head].dx = -1;
                        snake[snake_head].dy = 0;
                    }
                    else if ( event.key.keysym.sym == SDLK_RIGHT ) {
                        snake[snake_head].dx = +1;
                        snake[snake_head].dy = 0;
                    }
                    else if ( event.key.keysym.sym == SDLK_DOWN ) {
                        snake[snake_head].dx = 0;
                        snake[snake_head].dy = +1;
                    }
                    break;
                default:
                    break;
            }
        }    
       
       //Update game

        if ( ticks % 10 == 0 ) {
            #if 0
            for ( int i = snake_len - 1; i > 0; i-- ) {
                snake[i].x = snake[i-1].x;
                snake[i].y = snake[i-1].y;
            }
            #endif
            
            snake[snake_head].x += snake[snake_head].dx;
            snake[snake_head].y += snake[snake_head].dy;
        }
        
        if ( apple.x == snake[snake_head].x && apple.y == snake[snake_head].y ) {
            CollectAppleSoundEffect();
            apple.x = rand() % CONSOLE_W;
            apple.y = rand() % CONSOLE_H; 

        }  

        WarpToOppositeEnd(&snake[snake_head].x, &snake[snake_head].y, CONSOLE_W, CONSOLE_H, MIN_X, MIN_Y);
      
        //Draw game
        DOS_ClearScreen();
        RenderArrayEntity(snake, snake_head, snake_len);
        RenderEntity(&apple);
        DOS_DrawScreen();
    }    
    
    SDL_Quit();
    
    return EXIT_SUCCESS;
}