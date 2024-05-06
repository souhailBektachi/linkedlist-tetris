#pragma once

#include "enums.hpp"
#include "csts.hpp"
#include "Entity.hpp"
#include <iostream>

class icon : public Entity
{
private:
    IconType type;
    IconState state;
    SDL_Texture *normalTexture;
    SDL_Texture *hoverTexture;
    bool clicked;

public:
    icon(float x, float y, int h, int w, IconType type);
    icon();
    ~icon();
    void handleEvents(SDL_Event event);
    void update();
    void render(RenderWindow *renderer);
    IconState getState();
    static void loadTex(RenderWindow *renderer);
    bool getClicked();
    void setClicked(bool clicked);
};