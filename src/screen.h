#ifndef SCREEN_H
#define SCREEN_H

#include <inttypes.h>
#include <SDL2/SDL.h>

#include "canvas.h"

typedef struct {
  uint16_t width, height;
  SDL_Window* window;
  SDL_Renderer* renderer;
  Canvas* canvas;
} Screen;

Screen* screen_create(const int16_t width, const int16_t height);
void screen_present(const Screen* screen);
void screen_destroy(Screen* screen);

#endif
