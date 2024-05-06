#include "button.hpp"

button::button(float x, float y, SDL_Texture *texture, int h, int w, const char *font, RenderWindow **renderer, const char *text) : Entity(x, y, texture, h, w)
{
    this->renderer = *renderer;
    this->font = this->renderer->loadFont(font, 50);
    state = ButtonState::normal;
    normalTexture = this->renderer->loadTexture("assets/ui/btn.png");
    hoverTexture = this->renderer->loadTexture("assets/ui/btnHover.png");
    srcRect = {
        0,
        0,
        196, 84};
    setTexture(normalTexture);
    this->text = text;
}
button::button()
{
    this->renderer = NULL;
    this->text = NULL;
    this->font = NULL;
    state = ButtonState::normal;
    normalTexture = NULL;
    hoverTexture = NULL;
}
button::~button()
{
}
void button::handleEvents(SDL_Event event)
{

    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x > position.getX() && x < position.getX() + destRect.w && y > position.getY() && y < position.getY() + destRect.h)
    {
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            state = ButtonState::Clicked;
        }
        else
        {
            state = ButtonState::Hover;
        }
    }
    else
    {
        state = ButtonState::normal;
    }
}
void button::update(int cycle, double deltaTime)
{
    switch (state)
    {
    case ButtonState::normal:

        this->texture = normalTexture;
        break;
    case ButtonState::Hover:
        this->texture = hoverTexture;

        break;
    case ButtonState::Clicked:
        this->texture = hoverTexture;
        break;

    default:
        break;
    }
}
void button::render()
{
    int xP = position.getX() + 20;
    int yP = position.getY() + (destRect.h) / 4;
    // printf("x: %d, y: %d\n", destRect.x, destRect.y);
    renderer->render(this);
    renderer->renderText(text, font, (SDL_Color){164, 146, 95, 255}, xP, yP, destRect.h / 2, destRect.w - 40);
}
ButtonState button::getState()
{
    return state;
}