#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

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
    SDL_Surface *surface_text;
    SDL_Texture *texture_text;
    SDL_Rect renderQuad;
    SDL_Rect rect;
}Stack;