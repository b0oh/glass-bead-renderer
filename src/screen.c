#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "screen.h"

typedef struct {
  SDL_Window* window;
  SDL_Renderer* renderer;
  TTF_Font* font;
} ScreenPrivate;

static const uint8_t default_font_size = 16;

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

  ScreenPrivate* private = malloc(sizeof(ScreenPrivate));
  private->window = SDL_CreateWindow("Glass Bead Renderer",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    width, height,
    0);
  private->renderer = SDL_CreateRenderer(private->window, -1, SDL_RENDERER_ACCELERATED);
  private->font = TTF_OpenFont("pt-sans.ttf", default_font_size);

  Screen* screen = malloc(sizeof(Screen));
  screen->width = width;
  screen->height = height;
  screen->canvas = canvas_create(width, height);
  screen->private = (void*) private;

  return screen;
}

void screen_draw_canvas(const Screen* screen) {
  ScreenPrivate* private = (ScreenPrivate*) screen->private;

  SDL_Texture * texture = SDL_CreateTexture(private->renderer,
    SDL_PIXELFORMAT_ARGB8888,
    SDL_TEXTUREACCESS_STATIC,
    screen->canvas->width,
    screen->canvas->height);
  SDL_UpdateTexture(texture, NULL, screen->canvas->pixels, screen->canvas->pitch);
  SDL_RenderCopy(private->renderer, texture, NULL, NULL);
  SDL_DestroyTexture(texture);
}

void screen_draw_text(const Screen* screen, const char* text, const Color color, const Point point) {
  ScreenPrivate* private = (ScreenPrivate*) screen->private;

  SDL_Surface* surface = TTF_RenderText_Blended(private->font, text, translate_color(color));
  SDL_Texture* texture = SDL_CreateTextureFromSurface(private->renderer, surface);
  SDL_Rect rect;
  SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
  rect.x = point.x;
  rect.y = point.y;
  SDL_RenderCopy(private->renderer, texture, NULL, &rect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}

void screen_present(const Screen* screen) {
  SDL_RenderPresent(((ScreenPrivate*) screen->private)->renderer);
}

void screen_destroy(Screen* screen) {
  ScreenPrivate* private = (ScreenPrivate*) screen->private;

  canvas_destroy(screen->canvas);

  TTF_CloseFont(private->font);
  SDL_DestroyRenderer(private->renderer);
  SDL_DestroyWindow(private->window);
  free(private);
  free(screen);
  TTF_Quit();
  SDL_Quit();
}
