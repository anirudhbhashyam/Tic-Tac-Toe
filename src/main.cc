#include <iostream>

#include "renderer.hh"
#include "window.hh"
#include "game.hh"

#define WIDTH 800
#define HEIGHT 800
#define TITLE "Tic Tac Toe"
#define M 3
#define N 3


int main()
{
    Window win(WIDTH, HEIGHT, TITLE);
    Renderer r(win);
    Game g(r, 60, M, N);

    g.run();

    return 0;
}
