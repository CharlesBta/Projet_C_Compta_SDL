#include "include.h"
#include "struct.h"
#include <pthread.h>

#define WINDOWTITLE "SDL2 - Projet"
#define WINDOWWIDTH 1300
#define WINDOWHEIGHT 500
#define FPS 60

#define STACKWIDTH (int) ((WINDOWWIDTH - 300) / 3)
#define STACKHEIGHT (int) (WINDOWHEIGHT / 2)

#define POLICE_SIZE 23

Colors color[6]= {
        {.r = 0, .g = 0, .b = 0, .a = 255},
        {.r = 255, .g = 0, .b = 0, .a = 255, .text = "Pomme"},
        {.r = 0, .g = 255, .b = 0, .a = 255, .text = "Poire"},
        {.r = 255, .g = 255, .b = 0, .a = 255, .text = "Banane"},
        {.r = 255, .g = 165, .b = 0, .a = 255, .text = "Orange"},
        {.r = 255, .g = 0, .b = 255, .a = 255, .text = "Fraise"},
};

#include "tools_for_stock.c"

typedef struct arg{
    Stack *stacks;
    int indexMainStack;
}arg;

#include "tools_sort_stack.c"

// Définition des stacks
Stack stacks[6] = {
        {.x = 0, .y = 0, .w = STACKWIDTH, .h = STACKHEIGHT, .r = 200, .g=200, .b=200, .a=255, .ID = 0},
        {.x = STACKWIDTH, .y = 0, .w = STACKWIDTH, .h = STACKHEIGHT, .r = 150, .g=150, .b=150, .a=255, .ID = 1},
        {.x = 2 * STACKWIDTH, .y = 0, .w = STACKWIDTH, .h = STACKHEIGHT, .r = 200, .g=200, .b=200, .a=255, .ID = 2},
        {.x = 0, .y = STACKHEIGHT, .w = STACKWIDTH, .h = STACKHEIGHT, .r = 150, .g=150, .b=150, .a=255, .ID = 3},
        {.x = STACKWIDTH, .y = STACKHEIGHT, .w = STACKWIDTH, .h = STACKHEIGHT, .r = 200, .g=200, .b=200, .a=255, .ID = 4},
        {.x = 2 * STACKWIDTH, .y = STACKHEIGHT, .w = STACKWIDTH, .h = STACKHEIGHT, .r = 150, .g=150, .b=150, .a=255, .ID = 5}
};

Button sortButtonByQuantity = {.x = 3 * STACKWIDTH + 80, .y = WINDOWHEIGHT - 120, .w = 100, .h = 50, .text = "Sort by quantity"};
Button sortButtonByLetter = {.x = 3 * STACKWIDTH + 80, .y = WINDOWHEIGHT - 70, .w = 100, .h = 50, .text = "Sort by letter"};

Manager manager = {.x = 3 * STACKWIDTH, .y = 0, .r = 100, .g = 100, .b = 100, .a = 255};


void fillBackgroundStack(SDL_Renderer *renderer) {
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

    SDL_SetRenderDrawColor(renderer, manager.r, manager.g, manager.b, manager.a);
    SDL_RenderFillRect(renderer, &manager.rect);

    SDL_RenderCopy(renderer, manager.texture_text, NULL, &manager.renderQuad);

}

void fillButtons(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &sortButtonByQuantity.rect);
    SDL_RenderCopy(renderer, sortButtonByQuantity.texture_text, NULL, &sortButtonByQuantity.renderQuad);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &sortButtonByLetter.rect);
    SDL_RenderCopy(renderer, sortButtonByLetter.texture_text, NULL, &sortButtonByLetter.renderQuad);
}

void fillObjectInStack(SDL_Renderer *renderer) {
    for (int i = 0; i < 6; i++) {
        ObjectPile *pile = stacks[i].head;
        while (stacks[i].head != NULL) {
            SDL_SetRenderDrawColor(renderer, stacks[i].head->object->r, stacks[i].head->object->g, stacks[i].head->object->b, 255);
            SDL_RenderFillRect(renderer, &stacks[i].head->object->rect);
            stacks[i].head = stacks[i].head->next;
        }
        stacks[i].head = pile;
    }
}

void fillManagerText(SDL_Renderer *renderer, Manager *manager) {
    Text *text = manager->head;
    while (text != NULL) {
        SDL_RenderCopy(renderer, text->texture_text, NULL, &text->renderQuad);
        text = text->next;
    }
}

Bool handleOnZone(Mouse mouse, SDL_Rect zone)
{
    if (mouse.x >= zone.x && mouse.x <= zone.x + zone.w && mouse.y >= zone.y && mouse.y <= zone.y + zone.h)
    {
        return TRUE;
    }
    return FALSE;
}

int contentMain(SDL_Renderer *renderer)
{
    fillBackgroundStack(renderer);
    fillObjectInStack(renderer);
    fillManagerText(renderer, &manager);
    fillButtons(renderer);
}

int main(int argc, char *argv[]) {
#pragma region Initialisation de SDL
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL n'a pas pu s'initialiser ! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Initialisation de SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf n'a pas pu s'initialiser ! TTF_Error: %s\n", TTF_GetError());
        SDL_Quit();
        return -1;
    }

    // Création de la fenêtre
    SDL_Window *window = SDL_CreateWindow(WINDOWTITLE,
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          WINDOWWIDTH, WINDOWHEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("La fenêtre n'a pas pu être créée ! SDL_Error: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Création du renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Le renderer n'a pas pu être créé ! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Création de la police
    TTF_Font *font = TTF_OpenFont("arial.ttf", POLICE_SIZE);
    if (font == NULL) {
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
    SDL_Color textColorGray = {148, 148, 148, 255};  // Gray text

    stacks[0].rect = (SDL_Rect) {stacks[0].x, stacks[0].y, stacks[0].w, stacks[0].h};
    stacks[1].rect = (SDL_Rect) {stacks[1].x, stacks[1].y, stacks[1].w, stacks[1].h};
    stacks[2].rect = (SDL_Rect) {stacks[2].x, stacks[2].y, stacks[2].w, stacks[2].h};
    stacks[3].rect = (SDL_Rect) {stacks[3].x, stacks[3].y, stacks[3].w, stacks[3].h};
    stacks[4].rect = (SDL_Rect) {stacks[4].x, stacks[4].y, stacks[4].w, stacks[4].h};
    stacks[5].rect = (SDL_Rect) {stacks[5].x, stacks[5].y, stacks[5].w, stacks[5].h};
    manager.rect = (SDL_Rect) {manager.x, manager.y, WINDOWWIDTH-3*STACKWIDTH, WINDOWHEIGHT};

    manager.renderer = renderer;
    manager.font = font;

    manager.surface_text = TTF_RenderText_Solid(font, "Manager", textColorBlack);
    manager.texture_text = SDL_CreateTextureFromSurface(renderer, manager.surface_text);
    manager.renderQuad = (SDL_Rect) {manager.x + (((WINDOWWIDTH - 3 * STACKWIDTH))/2-(manager.surface_text->w/2)), manager.y+10, manager.surface_text->w, manager.surface_text->h};

    sortButtonByQuantity.surface_text = TTF_RenderText_Solid(font, sortButtonByQuantity.text, textColorBlack);
    sortButtonByQuantity.texture_text = SDL_CreateTextureFromSurface(renderer, sortButtonByQuantity.surface_text);
    sortButtonByQuantity.renderQuad = (SDL_Rect) {sortButtonByQuantity.x + 5, sortButtonByQuantity.y + 2, sortButtonByQuantity.surface_text->w, sortButtonByQuantity.surface_text->h};
    sortButtonByQuantity.rect = (SDL_Rect) {sortButtonByQuantity.x, sortButtonByQuantity.y, sortButtonByQuantity.surface_text->w + 20, sortButtonByQuantity.h};

    sortButtonByLetter.surface_text = TTF_RenderText_Solid(font, sortButtonByLetter.text, textColorBlack);
    sortButtonByLetter.texture_text = SDL_CreateTextureFromSurface(renderer, sortButtonByLetter.surface_text);
    sortButtonByLetter.renderQuad = (SDL_Rect) {sortButtonByLetter.x + 5, sortButtonByLetter.y + 2, sortButtonByLetter.surface_text->w, sortButtonByLetter.surface_text->h};
    sortButtonByLetter.rect = (SDL_Rect) {sortButtonByLetter.x , sortButtonByLetter.y, sortButtonByLetter.surface_text->w + 20, sortButtonByLetter.h};


#pragma endregion
    SDL_Event event;
    Bool running = TRUE;
    Mouse mouse;

    for (int i = 0; i < 5; ++i) {
        addObject(&stacks[0], creat_Object("Pomme"));
        addObject(&stacks[0], creat_Object("Poire"));
        addObject(&stacks[0], creat_Object("Banane"));
    }
    addObject(&stacks[0], creat_Object("Poire"));

    count(&manager, stacks, "Pomme");
    count(&manager, stacks, "Poire");
    count(&manager, stacks, "Banane");
    count(&manager, stacks, "Orange");
    count(&manager, stacks, "Fraise");

    deleteObject(&stacks[0], 0);

//    sortManagerByQuantity(&manager, &manager.head);
//    sortManagerByLetter(&manager, &manager.head);
    int done = 0;


    arg args = {.stacks = stacks, .indexMainStack = 0};
    pthread_t t1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = FALSE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&mouse.x, &mouse.y);
                    if (handleOnZone(mouse, sortButtonByQuantity.rect))
                    {
                        sortManagerByQuantity(&manager, &manager.head);
                    }
                    if (handleOnZone(mouse, sortButtonByLetter.rect))
                    {
                        sortManagerByLetter(&manager, &manager.head);
                    }
                    break;
            }
        }

        // Nettoyage de l'écran
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Dessiner la grille
        contentMain(renderer);
        if (done == 0)
        {
            pthread_create(&t1, NULL, (void *(*)(void *)) sort, &args);
            done = 1;
        }


        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }

    // Nettoyage et fermeture des bibliothèques et de SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
