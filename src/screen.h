#ifndef SCREEN_H
#define SCREEN_H

#include <inttypes.h>
#include "canvas.h"

typedef struct {
  uint16_t width, height;
  Canvas* canvas;
} Screen;

Screen* screen_create(int16_t width, int16_t height);
void screen_draw_canvas(const Screen* screen);
void screen_draw_text(const Screen* screen, const char* text, Color color, Point point);
void screen_present(const Screen* screen);
void screen_destroy(Screen* screen);

#endif
