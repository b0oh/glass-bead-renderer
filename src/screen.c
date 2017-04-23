#include <stdlib.h>

#include "screen.h"

Screen* screen_create(const int16_t width, const int16_t height) {
  SDL_Init(SDL_INIT_VIDEO);

  Screen* screen = malloc(sizeof(Screen));
  screen->width = width;
  screen->height = height;
  screen->window = SDL_CreateWindow("Glass Bead Renderer",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    width, height,
    0);
  screen->renderer = SDL_CreateRenderer(screen->window, -1, SDL_RENDERER_ACCELERATED);
  screen->canvas = canvas_create(width, height);

  return screen;
}

void screen_present(const Screen* screen) {
  SDL_Texture * texture = SDL_CreateTexture(screen->renderer,
    SDL_PIXELFORMAT_ARGB8888,
    SDL_TEXTUREACCESS_STATIC,
    screen->canvas->width,
    screen->canvas->height);
  SDL_UpdateTexture(texture, NULL, screen->canvas->pixels, screen->canvas->pitch);
  SDL_RenderCopy(screen->renderer, texture, NULL, NULL);
  SDL_DestroyTexture(texture);
  SDL_RenderPresent(screen->renderer);
}

void screen_destroy(Screen* screen) {
  canvas_destroy(screen->canvas);
  SDL_DestroyRenderer(screen->renderer);
  SDL_DestroyWindow(screen->window);
  free(screen);
  SDL_Quit();
}
