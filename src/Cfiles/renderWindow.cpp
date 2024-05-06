#include "renderWindow.hpp"

RenderWindow::RenderWindow(const char *p_title, int p_w, int p_h)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window failed to init. SDL_Error: %s\n", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

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
    dest = (SDL_Rect){(int)p_entity->getPosition().getX(), (int)p_entity->getPosition().getY(), p_entity->getDestRect().w, p_entity->getDestRect().h};
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
SDL_Renderer *RenderWindow::getRenderer()
{
    return renderer;
}
TTF_Font *RenderWindow::loadFont(const char *p_filePath, int p_size)
{
    TTF_Font *font = TTF_OpenFont(p_filePath, p_size);
    if (font == NULL)
    {
        printf("Failed to load font. SDL_Error: %s\n", SDL_GetError());
    }
    return font;
}
void RenderWindow::renderText(const char *p_text, TTF_Font *p_font, SDL_Color p_color, int p_x, int p_y, int h, int w)
{

    SDL_Surface *surface = TTF_RenderText_Solid(p_font, p_text, p_color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect;
    rect.x = p_x;
    rect.y = p_y;
    rect.w = w;
    rect.h = h;

    SDL_FreeSurface(surface);

    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}
void RenderWindow::destroyFont(TTF_Font *p_font)
{
    TTF_CloseFont(p_font);
}
void RenderWindow::renderTextWithmultipleColors(const char *p_text, TTF_Font *p_font, SDL_Color p_colors[], int p_x, int p_y)
{
    int text_length = strlen(p_text);
    SDL_Rect rect = {p_x, p_y, 0, 0};

    for (int i = 0; i < text_length; i++)
    {
        SDL_Surface *surface = TTF_RenderGlyph_Blended(p_font, p_text[i], p_colors[i]);
        if (surface == nullptr)
        {
            continue;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == nullptr)
        {
            SDL_FreeSurface(surface);
            continue;
        }

        rect.w = surface->w;
        rect.h = surface->h;

        SDL_RenderCopy(renderer, texture, nullptr, &rect);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);

        rect.x += rect.w;
    }
}
