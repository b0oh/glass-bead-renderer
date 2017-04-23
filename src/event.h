#ifndef EVENT_H
#define EVENT_H

#include <SDL2/SDL.h>

#define EVENT_QUIT SDL_QUIT

#define Event SDL_Event

inline int event_poll(Event* event) {
  return SDL_PollEvent(event);
}

#endif
