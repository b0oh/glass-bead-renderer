#pragma once

#include <inttypes.h>
#include "canvas.h"

typedef struct {
  Canvas* canvas;
} Screen;

Screen* screen_create(int16_t width, int16_t height);
void screen_draw_canvas(Screen* screen);
void screen_draw_text(Screen* screen, const char* text, Color color, Point point);
void screen_present(Screen* screen);
void screen_destroy(Screen* screen);
