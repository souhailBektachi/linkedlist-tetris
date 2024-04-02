#include "map.hpp"

Map::Map(const char *csvFile, SDL_Texture *maptexture)
{
    mapTilessize = (SDL_Rect){0, 0, 32, 32};
    mapTexture = maptexture;
    this->csvFile = csvFile;
    rendered = false;
    parseCsv(csvFile, mapKeys);
}
void Map::render(RenderWindow *renderer, textureSize texSize)
{
    int key, x, y;
    int srcSize = 16;
    int tilessize = (int)mapTilessize.h;

    int mapsHeight = SCREEN_HEIGHT / tilessize;
    int mapsWidth = SCREEN_WIDTH / tilessize;
    int k = 0;
    Entity *temp;
    for (int i = 0; i < mapsHeight * tilessize; i += tilessize)
    {
        for (int j = 0; j < mapsWidth * tilessize; j += tilessize)
        {
            key = mapKeys[k];
            k++;
            x = (key % texSize.w) * srcSize;
            y = (key / texSize.w) * srcSize;
            temp = &mapTiles[i / tilessize][j / tilessize];
            if (!rendered)
            {
                *temp = Entity(j, i, mapTexture, tilessize, tilessize);

                temp->setSrcRect((SDL_Rect){x, y, srcSize, srcSize});
                temp->setDestRect((SDL_Rect){j, i, tilessize, tilessize});
            }
            renderer->render(temp);
        }
    }
    rendered = true;
}
void Map::setRendered(bool value)
{
    rendered = value;
}
Map::~Map()
{
    SDL_DestroyTexture(mapTexture);
}