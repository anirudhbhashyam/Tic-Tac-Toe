#include "cell.hh"


Cell::Cell(int32_t x_, int32_t y_, uint32_t width_, uint32_t height_)
    : x(x_), y(y_), width(width_), height(height_)
{
    state = { false, -1 };
}

void Cell::draw(SDL_Renderer* renderer) const
{
    SDL_RenderDrawLine(
        renderer,
        x,
        y,
        x + width,
        y
    );

    SDL_RenderDrawLine(
        renderer,
        x,
        y,
        x,
        y + height
    );

    SDL_RenderDrawLine(
        renderer,
        x + width,
        y,
        x + width,
        y + height
    );

    SDL_RenderDrawLine(
        renderer,
        x,
        y + height,
        x + width,
        y + height
    );
}

void Cell::draw_cross(SDL_Renderer* renderer) const
{

    SDL_RenderDrawLine(
        renderer,
        x,
        y,
        x + width,
        y + height
    );

    SDL_RenderDrawLine(
        renderer,
        x + width,
        y,
        x,
        y + height
    );
}

void Cell::draw_knot(SDL_Renderer* renderer) const
{
    auto cx = x + width / 2;
    auto cy = y + height / 2;
    auto r = width / 2;

    for (uint32_t i{ 0 }; i < 360; i++)
    {
        auto x = cx + r * std::cos(i * M_PI / 180);
        auto y = cy + r * std::sin(i * M_PI / 180);

        SDL_RenderDrawPoint(renderer, x, y);
    }
}

bool Cell::is_clicked(int32_t mx, int32_t my) const
{
    return (
        mx >= x
        && mx <= (int32_t) (x + width)
        && my >= y 
        && my <= (int32_t) (y + height)
    );
}

void Cell::set_filled(bool val)
{
    state.filled = val;
}

void Cell::set_shape(int8_t shape)
{
    state.shape = shape;
}

void Cell::fill(SDL_Renderer* renderer, const int8_t turn) const
{
    if (turn == -1) return;

    if (turn == 1)
    {
        draw_cross(renderer);
    }
    else
    {
        draw_knot(renderer);
    }
}