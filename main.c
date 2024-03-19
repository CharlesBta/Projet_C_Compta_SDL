#include "include.h"
#include "struct.h"
#include "tools_for_stock.c"

#define WINDOWTITLE "SDL2 - Projet"
#define WINDOWWIDTH 1200
#define WINDOWHEIGHT 500
#define FPS 60

#define STACKWIDTH WINDOWWIDTH/3-60
#define STACKHEIGHT WINDOWHEIGHT/2

#define POLICE_SIZE 20


// Définition des stacks
Stack stacks[6] = {
    {.x = 0, .y = 0, .w = STACKWIDTH, .h = STACKHEIGHT, .r = 0, .g=0, .b=255, .a=255},
    {.x = STACKWIDTH, .y = 0, .w = STACKWIDTH, .h = STACKHEIGHT, .r = 0, .g=255, .b=0, .a=255},
    {.x = 2 * STACKWIDTH-60, .y = 0, .w = STACKWIDTH, .h = STACKHEIGHT, .r = 255, .g=0, .b=0, .a=255},
    {.x = 0, .y = STACKHEIGHT, .w = STACKWIDTH, .h = STACKHEIGHT, .r = 255, .g=165, .b=0, .a=255},
    {.x = STACKWIDTH, .y = STACKHEIGHT, .w = STACKWIDTH, .h = STACKHEIGHT, .r = 128, .g=0, .b=128, .a=255},
    {.x = 2 * STACKWIDTH-60, .y = STACKHEIGHT, .w = STACKWIDTH, .h = STACKHEIGHT, .r = 255, .g=192, .b=203, .a=255}
};


void fillBackgroundStack(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, stacks[0].r, stacks[0].g, stacks[0].b, stacks[0].a);
    SDL_RenderFillRect(renderer, &stacks[0].rect);

    SDL_SetRenderDrawColor(renderer, stacks[1].r, stacks[1].g, stacks[1].b, stacks[1].a);
    SDL_RenderFillRect(renderer, &stacks[1].rect);

    SDL_SetRenderDrawColor(renderer, stacks[2].r, stacks[2].g, stacks[2].b, stacks[2].a);
    SDL_RenderFillRect(renderer, &stacks[2].rect);

    SDL_SetRenderDrawColor(renderer, stacks[3].r, stacks[3].g, stacks[3].b, stacks[3].a);
    SDL_RenderFillRect(renderer, &stacks[3].rect);
    
    SDL_SetRenderDrawColor(renderer, stacks[4].r, stacks[4].g, stacks[4].b, stacks[4].a);
    SDL_RenderFillRect(renderer, &stacks[4].rect);

    SDL_SetRenderDrawColor(renderer, stacks[5].r, stacks[5].g, stacks[5].b, stacks[5].a);
    SDL_RenderFillRect(renderer, &stacks[5].rect);
    
}

void fillObjectInStack(SDL_Renderer *renderer)
{
    for (int i = 0; i < 6; i++)
    {
        ObjectPile *pile = stacks[i].head;
        while (stacks[i].head != NULL)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &stacks[i].head->object->rect);
            stacks[i].head = stacks[i].head->next;
        }
        stacks[i].head = pile;
    }
}



int main(int argc, char *argv[])
{
#pragma region Initialisation de SDL
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL n'a pas pu s'initialiser ! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Initialisation de SDL_ttf
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf n'a pas pu s'initialiser ! TTF_Error: %s\n", TTF_GetError());
        SDL_Quit();
        return -1;
    }

    // Création de la fenêtre
    SDL_Window *window = SDL_CreateWindow(WINDOWTITLE,
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          WINDOWWIDTH, WINDOWHEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("La fenêtre n'a pas pu être créée ! SDL_Error: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Création du renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Le renderer n'a pas pu être créé ! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Création de la police
    TTF_Font *font = TTF_OpenFont("arial.ttf", POLICE_SIZE);
    if (font == NULL)
    {
        printf("La police n'a pas pu être chargée ! TTF_Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Couleur du texte
    SDL_Color textColorWhite = {255, 255, 255, 255}; // White text
    SDL_Color textColorBlack = {0, 0, 0, 255};       // Black text
    SDL_Color textColorGray = {128, 128, 128, 255};  // Gray text

    stacks[0].rect = (SDL_Rect){stacks[0].x, stacks[0].y, stacks[0].w, stacks[0].h};
    stacks[1].rect = (SDL_Rect){stacks[1].x, stacks[1].y, stacks[1].w, stacks[1].h};
    stacks[2].rect = (SDL_Rect){stacks[2].x, stacks[2].y, stacks[2].w, stacks[2].h};
    stacks[3].rect = (SDL_Rect){stacks[3].x, stacks[3].y, stacks[3].w, stacks[3].h};
    stacks[4].rect = (SDL_Rect){stacks[4].x, stacks[4].y, stacks[4].w, stacks[4].h};
    stacks[5].rect = (SDL_Rect){stacks[5].x, stacks[5].y, stacks[5].w, stacks[5].h};
#pragma endregion
    SDL_Event event;
    Bool running = TRUE;
    Mouse mouse;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = FALSE;
                break;
            }
        }

        // Nettoyage de l'écran
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Dessiner la grille
        fillBackgroundStack(renderer);
        fillObjectInStack(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(1000/FPS);
    }

    // Nettoyage et fermeture des bibliothèques et de SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
