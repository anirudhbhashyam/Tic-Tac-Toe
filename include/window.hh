#pragma once

#include <iostream>
#include <stdint.h>
#include <string>

#include <SDL2/SDL.h>

#include "utils.hh"


class Window
{
    public:
        Window(uint32_t width_, uint32_t height_, const std::string& title_);
        ~Window();
        SDL_Window* get_screen_ref() const;
        int32_t get_width() const;
        int32_t get_height() const;
        void get_cell_sizes(int32_t, int32_t, int32_t&, int32_t&) const;

    private:
        SDL_Window* screen;
        std::string title;
};
