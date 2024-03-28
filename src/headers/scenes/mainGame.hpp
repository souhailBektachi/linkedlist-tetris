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
    mainScene();
    ~mainScene();
    void handleEvents();
    void update();
    void render();
    void setRenderer(RenderWindow *renderer);
    void spawnBlock();
};