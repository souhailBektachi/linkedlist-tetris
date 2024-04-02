#pragma once
#include "csts.hpp"
#include "entity.hpp"
#include "renderwindow.hpp"
#include "csvParser.hpp"
#include <stdbool.h>

class Map
{
private:
    bool rendered;
    const char *csvFile;
    SDL_Rect mapTilessize;
    Entity mapTiles[15][19];
    int mapKeys[285];
    SDL_Texture *mapTexture;

public:
    Map(const char *csvFile, SDL_Texture *mapTexture);
    ~Map();
    void render(RenderWindow *renderer, textureSize texSize);
    void setRendered(bool p_rendered);
};