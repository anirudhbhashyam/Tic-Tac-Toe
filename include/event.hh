#include <SDL2/SDL.h>

#include "utils.hh"

typedef struct
{
    int32_t x;
    int32_t y;
} Position;


class Event
{
    public:
        Event() = default;
        ~Event() = default;

        bool check_click();
        Position get_mouse_position();
};