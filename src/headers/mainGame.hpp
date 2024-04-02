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
using namespace std;
typedef struct gameBlock
{
    Block *NextBlock;
    int numberofBlocks;
    BlocksList Blocklist;
} gameBlock;
class mainScene
{
private:
    char *map;
    RenderWindow *renderer;
    Map *SceneMap;
    gameBlock gameBlocks;

public:
    mainScene(RenderWindow **renderer);
    ~mainScene();
    void handleEvents(SDL_Event event);
    void update(int cycle, double deltaTime);
    void render();
    void setRenderer(RenderWindow *renderer);
    void spawnBlock();
    void restart();
};