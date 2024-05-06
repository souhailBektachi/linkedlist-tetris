#pragma once
#include "window.hpp"
#include "button.hpp"
#include "icone.hpp"

class youLostwindow : public window
{

private:
    icon home;
    icon restart;
    const char *score;

public:
    youLostwindow(RenderWindow **renderer, const char *score);
    youLostwindow();
    ~youLostwindow();
    void render();
    void handleEvents(SDL_Event event);
    void update(int cycle, double deltaTime);
    void setScore(const char *score);
    icon *getHome();
    icon *getRestart();
};