#pragma once

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

#include "utils.hh"
#include "window.hh"
#include "cell.hh"


class Renderer
{
    public:
        Renderer(const Window& window);
        ~Renderer();
        void render();
        SDL_Renderer* get_renderer_ref() const;

        void set_color(uint32_t, uint32_t, uint32_t, uint32_t);

        void draw_background(uint32_t, uint32_t, uint32_t, uint32_t);

        void draw_grid(const std::vector<Cell>&);

        void clear();

        void update();

        void get_cell_sizes(int32_t, int32_t, int32_t&, int32_t&) const;

    private:
        SDL_Renderer* renderer;
        Window window;
};