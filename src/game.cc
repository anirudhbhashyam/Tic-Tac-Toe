#include "game.hh"


Game::Game(const Renderer& renderer_, uint32_t fps_, int32_t m_, int32_t n_)
    : fps(fps_), renderer(renderer_), m(m_), n(n_)
{
    sdl_error(SDL_Init(SDL_INIT_VIDEO));

    int32_t cw, ch;
    renderer.get_cell_sizes(m, n, cw, ch);

    for (auto i = 0; i < m * n; i++)
    {
        cells.emplace_back(
            (i % 3) * cw,
            (i / 3) * ch,
            cw,
            ch
        );
    }
}

Game::~Game()
{
    SDL_Quit();
}

auto Game::_tick(uint32_t ticks)
{
    auto now = SDL_GetTicks();
    return (now - ticks) >= 0 ? 0 : (ticks - now);
}

bool Game::check_win()
{
    // Check the rows.
    for (auto i{ 0 }; i < m; i += m)
    {
        int8_t temp_state = cells[0].get_shape();
        if (temp_state == -1) continue;
        int32_t count{ 0 };
        for (auto j{ 1 }; j < n; j++)
        {
            if (cells[i + j].get_shape() != temp_state) break;
            count += 1;
        }
        if (count == n - 1) return true;
    }

    return false;
}

void Game::run()
{
    bool running{ true };
    uint32_t ticks = SDL_GetTicks() + fps;
    SDL_Event event;

    uint8_t turn = 1;

    while (running)
    {
        SDL_Delay(_tick(ticks));
        
        renderer.set_color(40, 40, 40, 1);
        renderer.clear();

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    auto x = event.button.x;
                    auto y = event.button.y;
                    for (auto& cell: cells)
                    {
                        if (cell.is_filled()) continue;
                        if (cell.is_clicked(x, y))
                        {
                            turn++;
                            turn = turn % 2;
                            cell.set_filled();
                            cell.set_shape(turn);
                            break;
                        }
                    }
                    break;
            }
        }

        if (check_win())
        {
            std::cout << "You won!" << std::endl;
            running = false;
        }

        if (!running) break;

        renderer.draw_grid(cells);
        for (const auto& cell: cells)
        {   
            if (!cell.is_filled()) continue;
            renderer.set_color(255, 0, 0, 255);
            cell.fill(renderer.get_renderer_ref());
        }
        renderer.update();
    }
}

