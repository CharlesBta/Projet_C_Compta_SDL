#include "include.h"
#include "struct.h"

#define WINDOWTITLE "SDL2 - Projet"
#define WINDOWWIDTH 1200
#define WINDOWHEIGHT 500
#define FPS 60

#define STACKWIDTH WINDOWWIDTH/3
#define STACKHEIGHT WINDOWHEIGHT/2

#define POLICE_SIZE 20


// Définition des stacks
Stack stack1 = {.x = 0, .y = 0, .w = STACKWIDTH, .h = STACKHEIGHT, .r = 0, .g=0, .b=255, .a=255};
Stack stack2 = {.x = STACKWIDTH, .y = 0, .w = STACKWIDTH, .h = STACKHEIGHT, .r = 0, .g=255, .b=0, .a=255};
Stack stack3 = {.x = 2 * STACKWIDTH, .y = 0, .w = STACKWIDTH, .h = STACKHEIGHT, .r = 255, .g=0, .b=0, .a=255};
Stack stack4 = {.x = 0, .y = STACKHEIGHT, .w = STACKWIDTH, .h = STACKHEIGHT, .r = 255, .g=165, .b=0, .a=255};
Stack stack5 = {.x = STACKWIDTH, .y = STACKHEIGHT, .w = STACKWIDTH, .h = STACKHEIGHT, .r = 128, .g=0, .b=128, .a=255};
Stack stack6 = {.x = 2 * STACKWIDTH, .y = STACKHEIGHT, .w = STACKWIDTH, .h = STACKHEIGHT, .r = 255, .g=192, .b=203, .a=255};

void fillBackgroundStack(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, stack1.r, stack1.g, stack1.b, stack1.a);
    SDL_RenderFillRect(renderer, &stack1.rect);

    SDL_SetRenderDrawColor(renderer, stack2.r, stack2.g, stack2.b, stack2.a);
    SDL_RenderFillRect(renderer, &stack2.rect);

    SDL_SetRenderDrawColor(renderer, stack3.r, stack3.g, stack3.b, stack3.a);
    SDL_RenderFillRect(renderer, &stack3.rect);

    SDL_SetRenderDrawColor(renderer, stack4.r, stack4.g, stack4.b, stack4.a);
    SDL_RenderFillRect(renderer, &stack4.rect);
    
    SDL_SetRenderDrawColor(renderer, stack5.r, stack5.g, stack5.b, stack5.a);
    SDL_RenderFillRect(renderer, &stack5.rect);

    SDL_SetRenderDrawColor(renderer, stack6.r, stack6.g, stack6.b, stack6.a);
    SDL_RenderFillRect(renderer, &stack6.rect);
    
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

    stack1.rect = (SDL_Rect){stack1.x, stack1.y, stack1.w, stack1.h};
    stack2.rect = (SDL_Rect){stack2.x, stack2.y, stack2.w, stack2.h};
    stack3.rect = (SDL_Rect){stack3.x, stack3.y, stack3.w, stack3.h};
    stack4.rect = (SDL_Rect){stack4.x, stack4.y, stack4.w, stack4.h};
    stack5.rect = (SDL_Rect){stack5.x, stack5.y, stack5.w, stack5.h};
    stack6.rect = (SDL_Rect){stack6.x, stack6.y, stack6.w, stack6.h};



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
