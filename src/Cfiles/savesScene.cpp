#include "savesScene.hpp"

SavesScene::SavesScene(RenderWindow **renderer, LoadSave state, BlocksList *list)
{
    this->renderer = *renderer;
    this->font = this->renderer->loadFont(FONTS[1], 50);
    this->state = state;
    CreateSavesScene();
    this->list = list;
    this->load = false;
}
SavesScene::SavesScene()
{
    this->renderer = NULL;
    this->font = NULL;
    this->state = LoadSave::Load;
}
SavesScene::~SavesScene()
{
    SDL_DestroyTexture(uiElements.Background.getTexture());
    for (int i = 0; i < 15; i++)
    {
        SDL_DestroyTexture(uiElements.SaveSlots[i].getTexture());
    }
    renderer->destroyFont(font);
}

void SavesScene::CreateSavesScene()
{
    SDL_Texture *background = renderer->loadTexture("assets/ui/background.png");
    uiElements.Background = Entity(0, 0, background, SCREEN_HEIGHT, SCREEN_WIDTH);
    this->uiElements.Background.setSrcRect((SDL_Rect){
        0,
        650,
        5120 / 2,
        2880 - 1000});

    uiElements.Home = icon(279, 360, 50, 50, IconType::Home);
    if (state == LoadSave::Save)
    {

        uiElements.Home.setPosition({197,
                                     360});
        uiElements.Play = icon(361, 360, 50, 50, IconType::Play);
        uiElements.Play.setTexture(GlobalIcons[IconType::Play][iconNormal]);
    }

    uiElements.Home.setTexture(GlobalIcons[IconType::Home][iconNormal]);

    loadSaveSlots();
}

void SavesScene::loadSaveSlots()
{
    float x = 115;
    float y = 64;
    int counter = 0;
    for (int i = 0; i < 3; i++)
    {
        x = 115;
        for (int j = 0; j < 5; j++)
        {
            uiElements.SaveSlots[counter] = saveSlot(x, y, nullptr, 50, 50, FONTS[0], &renderer, counter);
            counter++;
            x += 82;
        }
        y += 93;
    }
}

void SavesScene::handleEvents(SDL_Event event)
{

    for (int i = 0; i < 15; i++)
    {
        if (state == LoadSave::Save)
            uiElements.SaveSlots[i].handleEvents(event, true, list);
        else
        {
            if (uiElements.SaveSlots[i].handleEvents(event, false, list))
            {
                load = true;
            }
        }
    }
    uiElements.Home.handleEvents(event);
    if (state == LoadSave::Save)
        uiElements.Play.handleEvents(event);
}

void SavesScene::update(int cycle, double deltaTime)
{
    for (int i = 0; i < 15; i++)
    {
        uiElements.SaveSlots[i].update(cycle, deltaTime);
    }
    uiElements.Home.update();
    if (state == LoadSave::Save)
        uiElements.Play.update();
}

void SavesScene::render()
{
    renderer->clear();
    renderer->render(&uiElements.Background);
    uiElements.Home.render(renderer);
    if (state == LoadSave::Save)
        uiElements.Play.render(renderer);
    renderSaveSlots();

    renderer->display();
}

void SavesScene::renderSaveSlots()
{
    for (int i = 0; i < 15; i++)
    {
        uiElements.SaveSlots[i].render();
    }
}
icon *SavesScene::getHome()
{
    return &uiElements.Home;
}
icon *SavesScene::getPlay()
{
    if (state == LoadSave::Save)
        return &uiElements.Play;
    return nullptr;
}
bool SavesScene::getLoad()
{
    return load;
}