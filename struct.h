/*
Macos : 
gcc main.c -o main $(sdl2-config --cflags --libs) -lSDL2_ttf -lSDL2_image
./main

Windows :
gcc -std=c17 main.c -IC:\SDL\Projet_C_Compta_SDL\SDL2\x86_64-w64-mingw32\
include -LC:\SDL\Projet_C_Compta_SDL\SDL2\x86_64-w64-mingw32\lib
 -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o main

*/

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

typedef struct colors {
    int r, g, b, a;
    char text[1024];
} colors;

typedef struct Object{
    int ID;
    char Name[50];
    int r, g, b, a;
    SDL_Rect rect;
}Object;

typedef struct ObjectPile{
    Object *object;
    struct ObjectPile *next;
}ObjectPile;

typedef struct Stack{
    int ID;
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

typedef struct Text{
    char text[1024];
    int quantity;
    int x,y;
    int r, g, b, a;
    SDL_Surface *surface_text;
    SDL_Texture *texture_text;
    SDL_Rect renderQuad;
    struct Text *next;
}Text;

typedef struct Manager{
    char title[1024];
    int x,y;
    int r, g, b, a;
    int quantity;
    SDL_Renderer *renderer;
    TTF_Font *font;
    SDL_Surface *surface_text;
    SDL_Texture *texture_text;
    SDL_Rect renderQuad;
    SDL_Rect rect;
    Text *head;
}Manager;