#include <SDL2/SDL.h>

#define GBR_EVENT_QUIT SDL_QUIT

#define GbrEvent SDL_Event

inline int gbr_poll_event(GbrEvent* event) {
  return SDL_PollEvent(event);
}
