#include "window.hpp"

window::window(const char *Title, RenderWindow **renderer)
{
    this->renderer = *renderer;
    SDL_Texture *backgroundTex = this->renderer->loadTexture("assets/ui/black.png");
    background = Entity(0, 0, backgroundTex, SCREEN_HEIGHT, SCREEN_WIDTH);
    background.setSrcRect({0,
                           0,
                           512, 512});
    Uint8 opacity = 240;
    background.setTextureOpacity(opacity);
    this->Title = Title;
    fonts[0] = this->renderer->loadFont(FONTS[0], 23);
    fonts[1] = this->renderer->loadFont(FONTS[1], 23);
}
window::~window()
{
    for (int i = 0; i < 2; i++)
        this->renderer->destroyFont(fonts[i]);
}
window::window()
{
}
void window::render()
{
    renderer->render(&background);
    renderer->renderText(Title, fonts[0], (SDL_Color){253, 226, 148, 255}, 191, 133, 51, 226);
}
