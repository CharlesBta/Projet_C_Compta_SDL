/*
Macos : 
gcc main.c -o main $(sdl2-config --cflags --libs) -lSDL2_ttf -lSDL2_image
./main

Windows :

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

typedef struct Object{
    int ID;
    char Name[50];
    SDL_Rect rect;
}Object;

typedef struct ObjectPile{
    Object *object;
    struct ObjectPile *next;
}ObjectPile;

typedef struct Stack{
    ObjectPile *head;
    int quantity;
    int x,y,h,w;
    char text[1024];
    SDL_Surface *surface_text;
    SDL_Texture *texture_text;
    SDL_Rect renderQuad;
    SDL_Rect rect;
}Stack;