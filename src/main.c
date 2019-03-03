#include <math.h>
#include <stdbool.h>

#include "screen.h"
#include "event.h"
#include "ticks.h"
#include "canvas.h"
#include "geometry.h"
#include "obj_loader.h"

static bool is_done() {
  Event event;

  while (event_poll(&event)) {
    if (event.type == EVENT_QUIT) {
      return true;
    }
  }

  return false;
}

static const char* fps(uint32_t previous_ticks, uint32_t current_ticks) {
  static char fps_buffer[128];
  uint32_t diff = current_ticks - previous_ticks;
  double fps = 1000.0f / diff;
  sprintf(fps_buffer, "%.1f", fps);
  return fps_buffer;
}

void wire_rasterizer(Canvas* canvas, const Mesh* mesh) {
  Color foreground = rgb(0, 0, 0);
  for (size_t tri_ix = 0; tri_ix < mesh->triangle_number; ++tri_ix) {
    Triangle triangle = mesh->triangles[tri_ix];

    for (int vertex_ix = 0; vertex_ix < 3; ++vertex_ix) {
      Vertex* v0 = triangle.vertices[vertex_ix];
      Vertex* v1 = triangle.vertices[(vertex_ix + 1) % 3];
      double horizontal_shift = (canvas->width - 1) / 2.;
      double vertical_shift = (canvas->height - 1) / 2.;
      double scale = vertical_shift;

      Point start = {
        round(v0->x * scale + horizontal_shift),
        round(-v0->y * scale + vertical_shift)
      };
      Point end = {
        round(v1->x * scale + horizontal_shift),
        round(-v1->y * scale + vertical_shift)
      };

      canvas_draw_line(canvas, foreground, start, end);
    }
  }
}

int main() {
  const size_t screen_width = 640;
  const size_t screen_height = 480;
  Screen* screen = screen_create(screen_width, screen_height);
  Canvas* canvas = screen->canvas;
  Color background = rgb(255, 255, 255);
  Color foreground = rgb(0, 0, 0);
  Mesh mesh = obj_loader_load("head.obj");
  uint32_t ticks = get_ticks();

  printf("Amount of triangles: %zu\n", mesh.triangle_number);

  while (!is_done()) {
    canvas_fill(canvas, background);
    wire_rasterizer(canvas, &mesh);
    screen_draw_canvas(screen);

    uint32_t new_ticks = get_ticks();
    const char* current_fps = fps(ticks, new_ticks);
    screen_draw_text(screen, current_fps, foreground, (Point) { .x = 10, .y = 10 });
    screen_present(screen);

    ticks = new_ticks;
  }

  screen_destroy(screen);

  return 0;
}
