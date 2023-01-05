#pragma once

#include <iostream>
#include <stdint.h>

#include <SDL2/SDL.h>

// Handle SDL errors.
inline void sdl_error(int32_t code)
{
    if (code < 0)
    {
        std::cerr << "SDL error: " << SDL_GetError() << std::endl;
        exit(1);
    }
}


template <typename T>
inline T* sdl_error_ptr(T* ptr)
{
    if (ptr == nullptr)
    {
        std::cerr << "SDL error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    return ptr;
}
