#pragma once
#include <iostream>
#include "csts.hpp"
#include "renderWindow.hpp"
#include "enums.hpp"
#include "Button.hpp"
using namespace std;

struct UiElements
{
    Entity Background;
    Entity Logo;
    button buttons[4];
};

class Menu
{
private:
    RenderWindow *renderer;
    UiElements uiElements;
    double deltaTime;
    TTF_Font *fonts[2];

public:
    Menu(RenderWindow **renderer);
    ~Menu();
    void handleEvents(SDL_Event event);
    void update(int cycle, double deltaTime);
    void render();
    void animateBackground(int cycle, double deltaTime);
    void CreateMenu(RenderWindow *renderer);
    void renderMenu();
    void handleMenuEvents(SDL_Event event);
    void renderText();
    void createButtons();
    GameState buttonsEvents();
};
