#include "pause.hpp"

pause::pause(RenderWindow **renderer) : window("Pause", renderer)
{
    home = icon(208, 255, 50, 50, IconType::Home);
    play = icon(278, 255, 50, 50, IconType::Play);
    restart = icon(348, 255, 50, 50, IconType::Restart);

    save = button(259, 195, nullptr, 33, 89, FONTS[0], renderer, "Save");
    home.setTexture(GlobalIcons[IconType::Home][iconNormal]);
    play.setTexture(GlobalIcons[IconType::Play][iconNormal]);
    restart.setTexture(GlobalIcons[IconType::Restart][iconNormal]);
}
pause::~pause()
{
}
pause::pause()
{
}
void pause::render()
{
    window::render();
    home.render(renderer);
    play.render(renderer);
    restart.render(renderer);
    save.render();
}

void pause::handleEvents(SDL_Event event)
{
    home.handleEvents(event);
    play.handleEvents(event);
    restart.handleEvents(event);
    save.handleEvents(event);
}
void pause::update(int cycle, double deltaTime)
{
    home.update();
    play.update();
    restart.update();
    save.update(cycle, deltaTime);
}
icon *pause::getHome()
{
    return &home;
}
icon *pause::getRestart()
{
    return &restart;
}
icon *pause::getPlay()
{
    return &play;
}
button *pause::getSave()
{
    return &save;
}
