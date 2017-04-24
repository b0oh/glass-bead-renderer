#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "screen.h"

typedef struct {
  Screen public;
  SDL_Window* window;
  SDL_Renderer* renderer;
  TTF_Font* font;
} ScreenPrivate;

static const uint8_t default_font_size = 16;

static SDL_Color translate_color(Color color) {
  return (SDL_Color) {
    (color & 0x00ff0000) / 0x10000,
    (color & 0x0000ff00) / 0x100,
    (color & 0x000000ff),
    255
  };
}

Screen* screen_create(int16_t width, int16_t height) {
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  ScreenPrivate* screen = malloc(sizeof(ScreenPrivate));
  screen->public.canvas = canvas_create(width, height);
  screen->window = SDL_CreateWindow("Glass Bead Renderer",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    width, height,
    0);
  screen->renderer = SDL_CreateRenderer(screen->window, -1, SDL_RENDERER_ACCELERATED);
  screen->font = TTF_OpenFont("pt-sans.ttf", default_font_size);

  return &screen->public;
}

void screen_draw_canvas(Screen* public_screen) {
  ScreenPrivate* screen = (ScreenPrivate*) public_screen;

  SDL_Texture * texture = SDL_CreateTexture(screen->renderer,
    SDL_PIXELFORMAT_ARGB8888,
    SDL_TEXTUREACCESS_STATIC,
    screen->public.canvas->width,
    screen->public.canvas->height);
  SDL_UpdateTexture(texture, NULL, screen->public.canvas->pixels, screen->public.canvas->pitch);
  SDL_RenderCopy(screen->renderer, texture, NULL, NULL);
  SDL_DestroyTexture(texture);
}

void screen_draw_text(Screen* public_screen, const char* text, Color color, Point point) {
  ScreenPrivate* screen = (ScreenPrivate*) public_screen;

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

void screen_present(Screen* screen) {
  SDL_RenderPresent(((ScreenPrivate*) screen)->renderer);
}

void screen_destroy(Screen* public_screen) {
  ScreenPrivate* screen = (ScreenPrivate*) public_screen;

  canvas_destroy(screen->public.canvas);

  TTF_CloseFont(screen->font);
  SDL_DestroyRenderer(screen->renderer);
  SDL_DestroyWindow(screen->window);
  free(screen);
  TTF_Quit();
  SDL_Quit();
}
