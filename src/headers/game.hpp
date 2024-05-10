#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>
#include "csts.hpp"
#include "renderWindow.hpp"
#include <stdbool.h>
#include "map.hpp"
#include "Entity.hpp"
#include "block.hpp"
#include "blocksList.hpp"
#include "enums.hpp"
#include "menu.hpp"
#include "mainGame.hpp"
#include "youLostwindow.hpp"
#include "savesScene.hpp"
using namespace std;

struct Scenes
{
    Menu *menu;
    mainScene *mainGame;
    SavesScene *saves;
};

class game
{
private:
    GameState gameState;
    RenderWindow *renderer;
    double deltaTime;
    bool isRunning;
    Scenes scenes;
    void *Scene;
    void resetGame();

public:
    game(const char *title);
    ~game();

    void handleEvents();
    void changeScene(GameState state);
    void update(double deltaTime);
    void render();
    bool getRunning();
    void handleButtonsEvents();
    void handlLostEvents();
    void handlePauseEvents();
    void handleSavesEvents();
    void handleSavesFromGame();
};
