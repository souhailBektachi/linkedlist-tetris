#pragma once
#include "window.hpp"
#include "button.hpp"
#include "icone.hpp"

class pause : public window
{
private:
    icon home;
    icon restart;
    icon play;
    button save;

public:
    pause(RenderWindow **renderer);
    pause();
    ~pause();
    void render();
    void handleEvents(SDL_Event event);
    void update(int cycle, double deltaTime);
    icon *getHome();
    icon *getRestart();
    icon *getPlay();
    button *getSave();
};