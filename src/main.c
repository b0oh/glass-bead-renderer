#include <stdbool.h>

#include "screen.h"
#include "canvas.h"
#include "event.h"
#include "ticks.h"

static inline bool is_done() {
  Event event;

  while (event_poll(&event)) {
    if (event.type == EVENT_QUIT) {
      return true;
    }
  }

  return false;
}

static inline const char* fps(uint32_t previous_ticks, uint32_t current_ticks) {
  static char fps_buffer[128];
  uint32_t diff = current_ticks - previous_ticks;
  double fps = 1000.0f / diff;
  sprintf(fps_buffer, "%.1f", fps);
  return fps_buffer;
}

static inline uint32_t drawing_loop(Screen* screen, uint32_t ticks) {
    for (int x = 300; x < 400; ++x) {
    for (int y = 300; y < 400; ++y) {
      canvas_draw_pixel(screen->canvas, rgb(255, 255, 0), (Point) {x, y});
    }
  }

  for (int i = 0; i < 256; ++ i) {
    Point start = {i, 0};
    Point end = {i + 20, screen->canvas->height - 1};
    canvas_draw_line(screen->canvas, rgb(i, 255, i), start, end);
  }

  screen_draw_canvas(screen);

  uint32_t new_ticks = get_ticks();

  screen_draw_text(screen, fps(ticks, new_ticks), rgb(0, 0, 255), (Point) { .x = 10, .y = 10 });
  screen_present(screen);

  return new_ticks;
}

static inline void loop(Screen* screen) {
  uint32_t ticks = get_ticks();

  while (!is_done()) {
    ticks = drawing_loop(screen, ticks);
  }
}

int main() {
  Screen* screen = screen_create(640, 480);

  loop(screen);

  screen_destroy(screen);

  return 0;
}
