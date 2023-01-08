#pragma once

#include <iostream>
#include <stdint.h>
#include <ranges>

#include <SDL2/SDL.h>

#include "renderer.hh"
#include "utils.hh"
#include "cell.hh"


class Game
{
    public:
        Game(const Renderer&, uint32_t, int32_t, int32_t);
        ~Game();
        bool check_win();
        void run();

    private:
        auto _tick(uint32_t);

    private:
        int32_t m;
        int32_t n;
        uint32_t fps;
        Renderer renderer;
        std::vector<Cell> cells;
};