#include "icone.hpp"

icon::icon(float x, float y, int h, int w, IconType type) : Entity(x, y, NULL, h, w)
{
    this->type = type;
    state = iconNormal;
    srcRect = {0, 0, 82, 82};
    clicked = false;
}
icon::~icon()
{
}
icon::icon()
{
}
void icon::handleEvents(SDL_Event event)
{
    if (event.type == SDL_MOUSEMOTION)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x > position.getX() && x < position.getX() + destRect.w && y > position.getY() && y < position.getY() + destRect.h)
        {
            state = iconHover;
        }
        else
        {
            state = iconNormal;
        }
    }
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x > position.getX() && x < position.getX() + destRect.w && y > position.getY() && y < position.getY() + destRect.h)
        {
            state = iconHover;
            clicked = true;
        }
    }
    if (event.type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x > position.getX() && x < position.getX() + destRect.w && y > position.getY() && y < position.getY() + destRect.h)
        {
            state = iconHover;
        }
        else
        {
            state = iconNormal;
        }
    }
}
void icon::update()
{
    texture = GlobalIcons[type][state];
}
void icon::render(RenderWindow *renderer)
{
    renderer->render(this);
}
IconState icon::getState()
{
    return state;
}
void icon::loadTex(RenderWindow *renderer)
{
    const char *icons[6][2] = {
        {"assets/ui/icons/Home.png",
         "assets/ui/icons/homeHover.png"},
        {"assets/ui/icons/play.png",
         "assets/ui/icons/playHover.png"},
        {"assets/ui/icons/pause.png",
         "assets/ui/icons/pauseHover.png"},
        {"assets/ui/icons/repeat.png",
         "assets/ui/icons/repeatHover.png"},
        {
            "assets/ui/left.png",
            "assets/ui/leftHover.png",
        },
        {
            "assets/ui/right.png",
            "assets/ui/rightHover.png",
        }};

    for (int i = 0; i < 4; i++)
    {
        GlobalIcons[i][iconNormal] = renderer->loadTexture(icons[i][0]);
        GlobalIcons[i][iconHover] = renderer->loadTexture(icons[i][1]);
    }
}
bool icon::getClicked()
{
    return clicked;
}
void icon::setClicked(bool clicked)
{
    this->clicked = clicked;
}