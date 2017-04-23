#include <stdbool.h>

#include "screen.h"
#include "canvas.h"
#include "event.h"

static inline bool is_done() {
  Event event;

  while (event_poll(&event)) {
    if (event.type == EVENT_QUIT) {
      return true;
    }
  }

  return false;
}

static inline void loop(const Screen* screen) {
  for (int x = 0; x < 100; ++x) {
    for (int y = 0; y < 100; ++y) {
      Point p = {x, y};
      canvas_draw_pixel(screen->canvas, rgb(255, 0, 255), p);
    }
  }

  screen_present(screen);

  if (!is_done()) {
    loop(screen);
  }
}

int main() {
  Screen* screen = screen_create(640, 480);

  loop(screen);

  screen_destroy(screen);

  return 0;
}
