#include <stddef.h>
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

void canvas_draw_line(const Canvas* canvas, const Color color, const Point start, const Point end) {
  int correction = 0,
    dx = end.x - start.x,
    dy = end.y - start.y,
    dx2 = dx * 2,
    dy2 = dy * 2;

  ptrdiff_t x_step = 1,
    y_step = canvas->width;

  if (dx < 0) {
    x_step = -1;
    dx = -dx;
  }

  if (dy < 0) {
    y_step = -canvas->width;
    dy = -dy;
  }

  Color* buffer = canvas->pixels + start.x + start.y * canvas->width;

  if (dx > dy) {
    correction = dy2 - dx;

    for (int ix = 0; ix <= dx; ++ix) {
      *buffer = color;

      if (correction >= 0) {
        correction -= dx2;
        buffer += y_step;
      }

      correction += dy2;
      buffer += x_step;
    }
  }
  else {
    correction = dx2 - dy;

    for (int ix = 0; ix <= dy; ++ix) {
      *buffer = color;

      if (correction >= 0) {
        correction -= dy2;
        buffer += x_step;
      }

      correction += dx2;
      buffer += y_step;
    }
  }
}

void canvas_destroy(Canvas* canvas) {
  free(canvas->pixels);
  free(canvas);
}
