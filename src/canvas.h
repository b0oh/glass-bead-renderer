#include <inttypes.h>
#include <SDL2/SDL.h>

typedef struct {
  const uint16_t width;
  const uint16_t height;
} GbrCanvasOptions;

typedef struct {
  SDL_Window* window;
} GbrCanvas;

GbrCanvas* gbr_create_canvas(const GbrCanvasOptions options);
void gbr_destroy_canvas(GbrCanvas* canvas);
