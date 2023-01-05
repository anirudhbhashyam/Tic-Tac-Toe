#include "event.hh"

Position Event::get_mouse_position()
{
    int32_t x, y;
    sdl_error(
        SDL_GetMouseState(&x, &y)
    );
    return { x, y };
}