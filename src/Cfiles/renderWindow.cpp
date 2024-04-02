#include "renderWindow.hpp"

RenderWindow::RenderWindow(const char *p_title, int p_w, int p_h)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window failed to init. SDL_Error: %s\n", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
    clear();
    display();
}
RenderWindow::RenderWindow()
{
    window = NULL;
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
void RenderWindow::render(Entity *p_entity)
{
    SDL_Rect src;
    src = (SDL_Rect){p_entity->getSrcRect().x, p_entity->getSrcRect().y, p_entity->getSrcRect().w, p_entity->getSrcRect().h};
    SDL_Rect dest;
    dest = (SDL_Rect){p_entity->getPosition().getX(), p_entity->getPosition().getY(), p_entity->getDestRect().w, p_entity->getDestRect().h};
    SDL_RendererFlip flip = p_entity->getRenderState() == Fliped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    if (SDL_RenderCopyEx(renderer, p_entity->getTexture(), &src, &dest, 0, NULL, flip) != 0)
    {
        printf("SDL_RenderCopyEx failed: %s\n", SDL_GetError());
    }
}

SDL_Texture *RenderWindow::loadTexture(const char *p_filePath)
{
    SDL_Texture *texture = IMG_LoadTexture(renderer, p_filePath);

    if (texture == NULL)
    {
        printf("Failed to load texture. SDL_Error: %s\n", SDL_GetError());
    }
    return texture;
}

void RenderWindow::rendernewcolor()
{
    SDL_SetRenderDrawColor(renderer, 33, 33, 0, 255);
    clear();
    display();
}