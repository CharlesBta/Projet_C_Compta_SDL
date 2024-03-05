#include "include.h"

#include "struct.h"

#define WINDOWTITLE "SDL2 - Projet"
#define WINDOWWIDTH 1600
#define WINDOWHEIGHT 800
#define FPS 60

#define POLICE_SIZE 20

int main(void)
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

    // Initialisation de SDL_image avec les formats PNG et JPG
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image n'a pas pu s'initialiser ! IMG_Error: %s\n", IMG_GetError());
        TTF_Quit();
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
        IMG_Quit();
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
        IMG_Quit();
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
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Couleur du texte
    SDL_Color textColorWhite = {255, 255, 255, 255}; // White text
    SDL_Color textColorBlack = {0, 0, 0, 255};       // Black text
    SDL_Color textColorGray = {128, 128, 128, 255};  // Gray text
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
            // Nettoyage de l'écran
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Dessin de l'écran
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }
    // Nettoyage et fermeture des bibliothèques et de SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}
