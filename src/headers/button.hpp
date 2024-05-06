#pragma once

#include <iostream>
#include "csts.hpp"
#include "renderWindow.hpp"
#include "enums.hpp"
#include "Entity.hpp"
using namespace std;
class button : public Entity
{
private:
    TTF_Font *font;
    const char *text;
    RenderWindow *renderer;
    ButtonState state;
    SDL_Texture *normalTexture;
    SDL_Texture *hoverTexture;

public:
    button(float x, float y, SDL_Texture *texture, int h, int w, const char *font, RenderWindow **renderer, const char *text);
    button();
    ~button();
    void handleEvents(SDL_Event event);
    void update(int cycle, double deltaTime);
    void render();
    ButtonState getState();
};