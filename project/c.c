#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window *window = SDL_CreateWindow("SDL2 Text", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font *font = TTF_OpenFont("font.ttf", 24);
    if (!font) {
        printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
        return 1;
    }

    SDL_Color textColor = {255, 255, 255}; // White
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Hello, SDL!", textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    SDL_Rect renderQuad = {100, 100, 200, 50}; // Set the position and size
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
    SDL_RenderPresent(renderer);

    SDL_Delay(3000); // Wait for 3 seconds

    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
