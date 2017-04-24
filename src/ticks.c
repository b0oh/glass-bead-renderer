#include <SDL2/SDL.h>

#include "ticks.h"

inline uint32_t get_ticks() {
  return SDL_GetTicks();
}
