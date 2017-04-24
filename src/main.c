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

static inline void loop(const Screen* screen, uint32_t ticks) {
  for (int x = 0; x < 100; ++x) {
    for (int y = 0; y < 100; ++y) {
      canvas_draw_pixel(screen->canvas, rgb(255, 255, 0), (Point) {x, y});
    }
  }

  screen_draw_canvas(screen);

  uint32_t new_ticks = get_ticks();

  screen_draw_text(screen, fps(ticks, new_ticks), rgb(0, 0, 255), (Point) { .x = 10, .y = 10 });
  screen_present(screen);

  if (!is_done()) {
    loop(screen, new_ticks);
  }
}

int main() {
  Screen* screen = screen_create(640, 480);

  loop(screen, get_ticks());

  screen_destroy(screen);

  return 0;
}
