#pragma once

#include <cmath>
#include <iostream>
#include <stdint.h>

#include <SDL2/SDL.h>

class CellState 
{
    public:
        bool filled;
        int8_t shape;
};


class Cell
{
    public:
        Cell(int32_t, int32_t, uint32_t, uint32_t);
        ~Cell() = default;

        void draw(SDL_Renderer*) const;
        void draw_cross(SDL_Renderer*) const;
        void draw_knot(SDL_Renderer*) const;

        bool is_clicked(int32_t, int32_t) const;

        bool is_filled() const { return state.filled; };
        void set_filled(bool = true);
        
        void set_shape(int8_t = -1);
        int8_t get_shape() const { return state.shape; };

        void fill(SDL_Renderer* renderer) const;

    public:
        int32_t x;
        int32_t y;
        uint32_t width;
        uint32_t height;
        CellState state;
};