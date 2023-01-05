#include "window.hh"


Window::Window(uint32_t width_, uint32_t height_, const char* title_)
    : title(title_)
{
    screen = sdl_error_ptr(
        SDL_CreateWindow(title, 0, 0, width_, height_, SDL_WINDOW_RESIZABLE)
    );
}

Window::~Window()
{
    SDL_DestroyWindow(screen);
}

SDL_Window* Window::get_screen_ref() const
{
    return screen;
}

int32_t Window::get_width() const
{
    int32_t w;
    SDL_GetWindowSize(screen, &w, nullptr);
    return w;
}

int32_t Window::get_height() const
{
    int32_t h;
    SDL_GetWindowSize(screen, nullptr, &h);
    return h;
}

void Window::get_cell_sizes(int32_t m, int32_t n, int32_t& w, int32_t& h) const
{
    w = get_width() / m;
    h = get_height() / n;
}