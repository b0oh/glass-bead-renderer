#include <stdlib.h>

#include "canvas.h"

Canvas* canvas_create(const int16_t width, const int16_t height) {
  Canvas* canvas = malloc(sizeof(Canvas));
  canvas->width = width;
  canvas->height = height;
  canvas->pitch = sizeof(Color) * width;
  canvas->pixels = malloc(canvas->pitch * height);

  return canvas;
}

void canvas_draw_pixel(const Canvas* canvas, const Color color, const Point point) {
  *(canvas->pixels + point.x + point.y * canvas->width) = color;
}

void canvas_destroy(Canvas* canvas) {
  free(canvas->pixels);
  free(canvas);
}
