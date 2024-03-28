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
void RenderWindow::render(Entity &p_entity)
{
    SDL_Rect src;
    src = (SDL_Rect){p_entity.getSrcRect().x, p_entity.getSrcRect().y, p_entity.getSrcRect().w, p_entity.getSrcRect().h};
    SDL_Rect dest;
    dest = (SDL_Rect){p_entity.getDestRect().x, p_entity.getDestRect().y, p_entity.getDestRect().w, p_entity.getDestRect().h};
    SDL_RendererFlip flip = p_entity.getRenderState() == Fliped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, p_entity.getTexture(), &src, &dest, 0, NULL, flip);
}

SDL_Texture *RenderWindow::loadTexture(const char *p_filePath)
{
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);
    if (texture == NULL)
    {
        printf("Failed to load texture. SDL_Error: %s\n", SDL_GetError());
    }
    return texture;
}
