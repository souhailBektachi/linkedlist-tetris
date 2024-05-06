#include "youLostwindow.hpp"

youLostwindow::youLostwindow(RenderWindow **renderer, const char *score) : window("You Lost", renderer)
{
    this->score = score;
    home = icon(213, 224, 50, 50, IconType::Home);
    restart = icon(323, 224, 50, 50, IconType::Restart);

    home.setTexture(GlobalIcons[IconType::Home][iconNormal]);
    restart.setTexture(GlobalIcons[IconType::Restart][iconNormal]);
}
youLostwindow::~youLostwindow()
{
}
youLostwindow::youLostwindow()
{
}
void youLostwindow::render()
{
    window::render();
    home.render(renderer);
    restart.render(renderer);
}

void youLostwindow::handleEvents(SDL_Event event)
{
    home.handleEvents(event);
    restart.handleEvents(event);
}
void youLostwindow::update(int cycle, double deltaTime)
{
    home.update();
    restart.update();
}
void youLostwindow::setScore(const char *score)
{
    this->score = score;
}
icon *youLostwindow::getHome()
{
    return &home;
}
icon *youLostwindow::getRestart()
{
    return &restart;
}