#pragma once

#include <iostream>
#include "csts.hpp"
#include "renderWindow.hpp"
#include "map.hpp"
#include "Entity.hpp"
#include "block.hpp"
#include "blocksList.hpp"
#include "enums.hpp"
#include <stdbool.h>
#include "youlostwindow.hpp"
#include "pause.hpp"
#include "savesScene.hpp"
using namespace std;
struct gameBlock
{
    Block *NextBlock;
    int numberofBlocks;
    BlocksList Blocklist;
};
struct MaingameUi
{
    Entity LeftArrow;
    Entity RightArrow;
    SDL_Texture *left;
    SDL_Texture *right;
    SDL_Texture *leftPressed;
    SDL_Texture *rightPressed;
};
class mainScene
{
private:
    char *map;
    RenderWindow *renderer;
    Map *SceneMap;
    gameBlock gameBlocks;
    MaingameUi ui;
    bool UsedShift;
    TTF_Font *score;
    youLostwindow *lostWindow;
    SavesScene *savesScene;

    pause *pauseWindow;

public:
    bool lost;
    bool paused;
    bool saved;
    mainScene(RenderWindow **renderer);
    ~mainScene();
    void handleEvents(SDL_Event event);
    void update(int cycle, double deltaTime);
    void render();
    void setRenderer(RenderWindow *renderer);
    void spawnBlock();
    void restart();
    void handleEventsArrowsUp(SDL_Event event);
    void initUi();
    void lostGame();
    void pauseGame();
    youLostwindow *getLostWindow();
    pause *getPauseWindow();
    SavesScene *getSavesScene();
    BlocksList *getBlocksList();
    void setSaved(bool saved);
};