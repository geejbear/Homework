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

#define CONSOLE_W 15
#define CONSOLE_H 15
#define CONSOLE_SIZE (CONSOLE_W * CONSOLE_H)

#define MIN_X 0
#define MIN_Y 0

#define FPS 30
#define SECONDS(x) (int)((float)(x) * (float)FPS)
#define UPDATE_INTERVAL_TICKS 15 // how often (interval) does game update
#define SNAKE_INITIAL_LENGTH 3 
#define SNAKE_MAX_LEN CONSOLE_SIZE

void RenderApple(int x, int y, char ch, int fc) // Apple is an entity
{
    DOS_GotoXY(x, y);
    DOS_SetForeground(fc);
    DOS_PrintChar(ch); 
}

// example: probably better than a macro
int SecondsToTicks(float seconds)
{
    return seconds * (float)FPS;
}

void CollectAppleSoundEffect(void)
{
    DOS_InitSound();
    DOS_Sound(880, 70);        
    DOS_Sound(1720, 70);
}

void RenderSnakeBackToStart(int point_x[], int point_y[])
{
    for ( int i = 0; i < SNAKE_MAX_LEN; i++ ) {
        point_x[i] = CONSOLE_W / 2;
        point_y[i] = CONSOLE_H / 2 + i;
    }
}

typedef struct {
    int x;
    int y;
    bool active; // TF: no
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
int dx, dy;
Point snake[SNAKE_MAX_LEN];
int snake_len = SNAKE_INITIAL_LENGTH; // num of segments in snake

#if 0
int map[CONSOLE_H][CONSOLE_W] = {
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
};
#endif

/* void Input(int key, bool running, SDL_Event event)
{
    switch ( key ) {

        case SDLK_ESCAPE:
            if ( event.key.keysym.sym == SDLK_ESCAPE ) {
                running = false;
            }
            break;
        case SDLK_UP:
            if ( event.key.keysym.sym == SDLK_UP ) {
                dx = 0;
                dy = -1;
            }
            break;
        case SDLK_LEFT:
            if ( event.key.keysym.sym == SDLK_LEFT ) {
                dx = -1;
                dy = 0;
            }
            break;
        case SDLK_RIGHT:
            if ( event.key.keysym.sym == SDLK_RIGHT ) {
                dx = +1;
                dy = 0;
            }
            break;
        case SDLK_DOWN:
            if ( event.key.keysym.sym == SDLK_DOWN ) {
                dx = 0;
                dy = +1;
            }
            break;
        default:
            break;
    }
} */

void DrawSnake() {
    for ( int i = 0; i < snake_len; i++ ) {
        DOS_GotoXY(snake[i].x, snake[i].y);
        DOS_SetForeground(DOS_GREEN);
        DOS_PrintChar(0xB1);
    }
}

int main()
{
    //init console
    if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) {
        fprintf(stderr, "Error: SDL_Init() failed! (%s)\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    DOS_InitScreen("Bounder", CONSOLE_W, CONSOLE_H, DOS_MODE40, 4);
    //DOS_InitSound();
    DOS_SetScreenScale(3);
    DOS_SetCursorType(DOS_CURSOR_NONE);
    
    //===================================================
    
    // initial snake
    snake[snake_len].active = true; // ??
    
    for ( int i = 0; i < snake_len; i++ ) {
        snake[i].x = CONSOLE_W / 2;
        snake[i].y = CONSOLE_H / 2 + i; 
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

    
    //RenderApple(apple.x, apple.y, apple.ch, apple.fc);

    //===================================================

    // program loop:
    dx = 0, dy = -1; // TF: game design: dx/dy both 0
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
                    //Input(SDL_KEYDOWN, running, event);
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

        // make snake "wrap around" to other side of screen
#if 0
        if (( snake[0].x == MIN_X  || snake[0].x == CONSOLE_W - 1 ) || 
             ( snake[0].y == MIN_Y || snake[0].y == CONSOLE_H - 1)) {
            snake_len = SNAKE_INITIAL_LENGTH;
            
        }

        //if head collides with body, snakes jumps back to the start position
        for ( int i = snake_len; i > 1; i-- ) {
            if (( snake[0].x == snake[i].x) && (snake[0].y == snake[i].y )) {
                
                snake_len = SNAKE_INITIAL_LENGTH;
                
            }
        }
#endif
        
        //===============================================

        // 2) SIMULATE/UPDATE GAME

        if ( apple.x == snake[0].x && apple.y == snake[0].y ) {
            // eat the apple
            CollectAppleSoundEffect();
            
            apple.x = rand() % CONSOLE_W;
            apple.y = rand() % CONSOLE_H;
            
            snake_len++;

        }

        // move the snake
        if ( ticks % SECONDS(0.3f) == 0 ) {
            // temp: dx dy affects head of snake
            for ( int i = SNAKE_MAX_LEN; i > 0; i-- ) {
                snake[i].x = snake[i-1].x;
                snake[i].y = snake[i-1].y;
            } 
            snake[0].x += dx;
            snake[0].y += dy;
        }

        //===============================================
        // 3) RENDER GAME
        
        DOS_ClearScreen();
        RenderApple(apple.x, apple.y, apple.ch, apple.fc);
        DrawSnake();
        DOS_DrawScreen();
    }
    
    // exit program:
    
    SDL_Quit();
    
    return EXIT_SUCCESS;
}





// was in drawing section, should be in update section
#if 0
        if ( apple.active )  {
            for ( int i = snake_len; i > 1; i-- ) {
                if (( apple.x != snake[i].x ) && ( apple.y != snake[i].y )) {
                        RenderApple(apple.x, apple.y, apple.ch, apple.fc);
                }
            }
        }
#endif





// drawing map array
#if 0
        int y, x = 0; // TF: make local
        for ( y = 0; y < CONSOLE_H; y++ ) {
            for ( x = 0; x < CONSOLE_W; x++ ) {
                if (map[y][x]) {
                    DOS_GotoXY(x, y);
                    DOS_SetForeground(DOS_GRAY);
                    DOS_PrintChar(219);
                }
            }
        }
#endif
