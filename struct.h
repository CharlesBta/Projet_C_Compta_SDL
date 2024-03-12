/*
Macos : 
gcc main.c -o main $(sdl2-config --cflags --libs) -lSDL2_ttf -lSDL2_image
./main

Windows :
gcc -std=c17 main.c -IC:\SDL\Projet_C_Compta_SDL\SDL2\x86_64-w64-mingw32\
include -LC:\SDL\Projet_C_Compta_SDL\SDL2\x86_64-w64-mingw32\lib
 -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o main


*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef enum Bool
{
    FALSE,
    TRUE
} Bool;

typedef struct Mouse
{
    int x;
    int y;
} Mouse;

typedef struct Object{
    char Name[50];
}Object;

typedef struct ObjectPile{
    Object *object;
    struct Object *next;
}ObjectPile;

typedef struct Stack{
    ObjectPile *head;
    int quantity;
    int x,y,h,w;
    char text[1024];
    int r, g, b, a;
    SDL_Surface *surface_text;
    SDL_Texture *texture_text;
    SDL_Rect renderQuad;
    SDL_Rect rect;
}Stack;