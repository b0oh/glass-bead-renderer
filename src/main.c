#include <stdbool.h>

#include "canvas.h"
#include "event.h"

void main_loop() {
  bool is_done = false;
  GbrEvent e;

  while (!is_done) {
    while (gbr_poll_event(&e)) {
      if (e.type == GBR_EVENT_QUIT) {
        is_done = true;
      }
    }
  }
}

int main() {
  GbrCanvasOptions canvas_options = {
    .width = 640,
    .height = 480
  };
  GbrCanvas* canvas = gbr_create_canvas(canvas_options);

  main_loop();

  gbr_destroy_canvas(canvas);

  return 0;
}
