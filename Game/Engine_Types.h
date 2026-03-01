#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

typedef struct{
    int Input[256];
} Game;

typedef struct 
{
    float x;
    float y;
} Vector2;

typedef struct
{
    int r;
    int g;
    int b;
    int a;
} Color;
