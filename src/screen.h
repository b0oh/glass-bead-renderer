#ifndef SCREEN_H
#define SCREEN_H

#include <inttypes.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "canvas.h"

typedef struct {
  uint16_t width, height;
  Canvas* canvas;
  SDL_Window* window;
  SDL_Renderer* renderer;
  TTF_Font* font;
} Screen;

Screen* screen_create(const int16_t width, const int16_t height);
void screen_draw_canvas(const Screen* screen);
void screen_draw_text(const Screen* screen, const char* text, const Color color, const Point point);
void screen_present(const Screen* screen);
void screen_destroy(Screen* screen);

#endif
