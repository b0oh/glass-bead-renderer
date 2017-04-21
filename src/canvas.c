#include <stdlib.h>

#include "canvas.h"

GbrCanvas* gbr_create_canvas(const GbrCanvasOptions options) {
  SDL_Init(SDL_INIT_VIDEO);
  GbrCanvas* canvas = malloc(sizeof(GbrCanvas));
  canvas->window = SDL_CreateWindow("Very Cool Software Renderer",
                                    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                    options.width, options.height, 0);

  return canvas;
}

void gbr_destroy_canvas(GbrCanvas* canvas) {
  SDL_DestroyWindow(canvas->window);
  free(canvas);
  SDL_Quit();
}
