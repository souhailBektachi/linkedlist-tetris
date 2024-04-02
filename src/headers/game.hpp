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
#include "mainGame.hpp"
using namespace std;

class game
{
private:
    GameState gameState;
    RenderWindow *renderer;
    double deltaTime;
    bool isRunning;
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
};