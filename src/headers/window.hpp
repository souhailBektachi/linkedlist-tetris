#pragma once

#include "Entity.hpp"
#include "enums.hpp"
#include "renderWindow.hpp"
#include <iostream>

class window
{
protected:
    Entity background;
    RenderWindow *renderer;
    TTF_Font *fonts[2];
    const char *Title;

public:
    window(const char *Title, RenderWindow **renderer);
    window();
    ~window();
    void render();
    static void loadIcons(RenderWindow *renderer);
};