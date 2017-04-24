#include <stdlib.h>

#include "screen.h"

static inline SDL_Color translate_color(Color color) {
  return (SDL_Color) {
    (color & 0x00ff0000) / 0x10000,
    (color & 0x0000ff00) / 0x100,
    (color & 0x000000ff),
    255
  };
}

Screen* screen_create(const int16_t width, const int16_t height) {
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  Screen* screen = malloc(sizeof(Screen));
  screen->width = width;
  screen->height = height;
  screen->window = SDL_CreateWindow("Glass Bead Renderer",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    width, height,
    0);
  screen->renderer = SDL_CreateRenderer(screen->window, -1, SDL_RENDERER_ACCELERATED);
  screen->font = TTF_OpenFont("pt-sans.ttf", 16);
  screen->canvas = canvas_create(width, height);

  return screen;
}

void screen_draw_canvas(const Screen* screen) {
  SDL_Texture * texture = SDL_CreateTexture(screen->renderer,
    SDL_PIXELFORMAT_ARGB8888,
    SDL_TEXTUREACCESS_STATIC,
    screen->canvas->width,
    screen->canvas->height);
  SDL_UpdateTexture(texture, NULL, screen->canvas->pixels, screen->canvas->pitch);
  SDL_RenderCopy(screen->renderer, texture, NULL, NULL);
  SDL_DestroyTexture(texture);
}

void screen_draw_text(const Screen* screen, const char* text, const Color color, const Point point) {
  SDL_Surface* surface = TTF_RenderText_Blended(screen->font, text, translate_color(color));
  SDL_Texture* texture = SDL_CreateTextureFromSurface(screen->renderer, surface);
  SDL_Rect rect;
  SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
  rect.x = point.x;
  rect.y = point.y;
  SDL_RenderCopy(screen->renderer, texture, NULL, &rect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}

void screen_present(const Screen* screen) {
  SDL_RenderPresent(screen->renderer);
}

void screen_destroy(Screen* screen) {
  canvas_destroy(screen->canvas);
  TTF_CloseFont(screen->font);
  SDL_DestroyRenderer(screen->renderer);
  SDL_DestroyWindow(screen->window);
  free(screen);
  TTF_Quit();
  SDL_Quit();
}
