#include "renderer.hh"

class Cell;

Renderer::Renderer(const Window& window_)
    : window(window_)
{
    renderer = sdl_error_ptr(
        SDL_CreateRenderer(window.get_screen_ref(), -1, SDL_RENDERER_ACCELERATED)
    );
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(renderer);
}

void Renderer::clear()
{
    sdl_error(SDL_RenderClear(renderer));
}

void Renderer::update()
{
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Renderer::get_renderer_ref() const
{
    return renderer;
}

void Renderer::set_color(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
    sdl_error(SDL_SetRenderDrawColor(renderer, r, g, b, a));
}

void Renderer::draw_background(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
    set_color(r, g, b, a);
}

void Renderer::draw_grid(const std::vector<Cell>& cells)
{
    set_color(255, 255, 255, 255);

    for (const auto& cell: cells)
    {
        cell.draw(renderer);
    }
}

void Renderer::get_cell_sizes(int32_t m, int32_t n, int32_t& w, int32_t& h) const
{
    w = window.get_width() / m;
    h = window.get_height() / n;
}