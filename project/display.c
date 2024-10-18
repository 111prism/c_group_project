#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>

bool isPointInRect(int x, int y, SDL_Rect* rect) {
    return (x >= rect->x && x <= (rect->x + rect->w) &&
            y >= rect->y && y <= (rect->y + rect->h));
}

SDL_Texture* loadTexture(const char *file, SDL_Renderer *renderer) {
    SDL_Surface *surface = IMG_Load(file);
    if (!surface) {
        printf("Unable to load image %s! SDL_image Error: %s\n", file, IMG_GetError());
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1) {
        printf("Could not initialize SDL_ttf: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {  // Initialize PNG support
        printf("Could not initialize SDL_image: %s\n", IMG_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Time Clock", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 525, 675, 0);
    if (!window) {
        printf("Could not create window: %s\n", SDL_GetError());
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        printf("Could not create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Texture *image1 = loadTexture("Start.png", renderer);
    SDL_Texture *image2 = loadTexture("Stop.png", renderer);
    if (!image1 || !image2) {
        SDL_DestroyTexture(image1);
        SDL_DestroyTexture(image2);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Texture *imageTexture = image1;
    SDL_Rect buttonRect = {162, 237, 200, 200};

    TTF_Font *font = TTF_OpenFont("font.ttf", 24);
    if (!font) {
        printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
        SDL_DestroyTexture(image1);
        SDL_DestroyTexture(image2);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Color textColor = {255, 255, 255};
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Hello, SDL!", textColor);
    if (!textSurface) {
        printf("Unable to render text surface! TTF_Error: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        SDL_DestroyTexture(image1);
        SDL_DestroyTexture(image2);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    SDL_Rect textRect = {100, 100, 200, 50};

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (isPointInRect(event.button.x, event.button.y, &buttonRect)) {
                    imageTexture = (imageTexture == image1) ? image2 : image1;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, imageTexture, NULL, &buttonRect);
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(image1);
    SDL_DestroyTexture(image2);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
