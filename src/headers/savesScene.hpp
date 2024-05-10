#pragma once
#include "csts.hpp"
#include "Button.hpp"
#include "saveSlot.hpp"
#include "enums.hpp"
#include "icone.hpp"
#include <dirent.h>
#include "blocksList.hpp"

#include <iostream>
#include "renderWindow.hpp"
struct SaveUiElements
{
    Entity Background;
    saveSlot SaveSlots[15];
    icon Home;
    icon Play;
};
class SavesScene
{
private:
    RenderWindow *renderer;
    SaveUiElements uiElements;
    TTF_Font *font;
    LoadSave state;
    BlocksList *list;
    bool load;

public:
    SavesScene(RenderWindow **renderer, LoadSave state, BlocksList *list);
    SavesScene();
    ~SavesScene();
    void CreateSavesScene();
    void loadSaveSlots();
    void handleEvents(SDL_Event event);
    void update(int cycle, double deltaTime);
    void render();
    void renderSaveSlots();
    icon *getHome();
    icon *getPlay();
    bool getLoad();
};
