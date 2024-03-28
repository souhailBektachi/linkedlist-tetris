#include "renderWindow.hpp"

RenderWindow::RenderWindow(const char *p_title, int p_w, int p_h)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window failed to init. SDL_Error: %s\n", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}
RenderWindow::~RenderWindow()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}
void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}
void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}
void RenderWindow::render(Entity &p_entity, renderState p_state)
{
}