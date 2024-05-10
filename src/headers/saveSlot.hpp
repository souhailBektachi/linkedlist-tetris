#pragma once
#include "Entity.hpp"
#include <fstream>
#include <sys/stat.h>
#include "blocksList.hpp"
#include "enums.hpp"

class saveSlot : public Entity
{
private:
    int id;
    TTF_Font *font;
    const char *text;
    RenderWindow *renderer;
    savedState Savedstate;
    ButtonState state;

public:
    saveSlot(float x, float y, SDL_Texture *texture, int h, int w, const char *font, RenderWindow **renderer,int id);
    saveSlot();
    ~saveSlot();
    bool handleEvents(SDL_Event event, bool flag, BlocksList *list);
    void update(int cycle, double deltaTime);
    void render();
    savedState getState();
    void renderSaveState();
    const char *loadSaveState(savedState state);
    void saveTo(BlocksList *list);
     
};