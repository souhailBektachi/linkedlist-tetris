#include "mainGame.hpp"
mainScene::mainScene(RenderWindow **renderer)
{
    this->renderer = *renderer;
    Block::loadTex(this->renderer);

    gameBlocks.numberofBlocks = 0;
    gameBlocks.Blocklist.setmaxSize(17);

    SDL_Texture *maptex = this->renderer->loadTexture("assets/gfx/Texture.png");

    SceneMap = new Map("assets/maps/secondmap.csv", maptex);
    this->score = this->renderer->loadFont(FONTS[1], 24);
    initUi();
    spawnBlock();
    UsedShift = false;
    lost = false;
    lostWindow = new youLostwindow(renderer, "Score: 0");
    paused = false;
    pauseWindow = new pause(renderer);
    savesScene = new SavesScene(renderer, LoadSave::Save, &gameBlocks.Blocklist);
    gameBlocks.Blocklist.SaveLoadHighscore();
    saved = false;
}

void mainScene::initUi()
{
    ui.left = this->renderer->loadTexture("assets/ui/left.png");
    ui.right = this->renderer->loadTexture("assets/ui/right.png");
    ui.leftPressed = this->renderer->loadTexture("assets/ui/leftHover.png");
    ui.rightPressed = this->renderer->loadTexture("assets/ui/rightHover.png");
    ui.LeftArrow = Entity(20, (SCREEN_HEIGHT / 2) - 32, ui.left, 64, 64);
    ui.RightArrow = Entity(SCREEN_WIDTH - 64 - 20, (SCREEN_HEIGHT / 2) - 32, ui.right, 64, 64);
    ui.LeftArrow.setSrcRect((SDL_Rect){0, 0, 84, 84});
    ui.RightArrow.setSrcRect((SDL_Rect){0, 0, 84, 84});
}
mainScene::~mainScene()
{
    delete SceneMap;
    delete lostWindow;
    delete pauseWindow;
    delete savesScene;
    SDL_DestroyTexture(ui.left);
    SDL_DestroyTexture(ui.right);
    SDL_DestroyTexture(ui.leftPressed);
    SDL_DestroyTexture(ui.rightPressed);
    delete gameBlocks.NextBlock;
    gameBlocks.Blocklist.deleteList();
    renderer->destroyFont(score);
}
void mainScene::handleEvents(SDL_Event event)
{
    if (!lost && !paused && !saved)
    {
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                if (gameBlocks.NextBlock->move(LEFT))
                {
                    gameBlocks.Blocklist.insertAtHead(gameBlocks.NextBlock);
                }
                ui.LeftArrow.setTexture(ui.leftPressed);
                break;
            case SDLK_RIGHT:
                if (gameBlocks.NextBlock->move(RIGHT))
                {
                    gameBlocks.Blocklist.insert(gameBlocks.NextBlock);
                }
                ui.RightArrow.setTexture(ui.rightPressed);
                break;

            case SDLK_c:
                if (!UsedShift)
                {
                    gameBlocks.Blocklist.shift(Color, *gameBlocks.NextBlock);
                    UsedShift = true;
                }
                break;
            case SDLK_t:
                if (!UsedShift)
                {
                    gameBlocks.Blocklist.shift(Type, *gameBlocks.NextBlock);
                    UsedShift = true;
                }
                break;
            }
        }

        else if (event.type == SDL_KEYUP)
        {
            handleEventsArrowsUp(event);
        }
    }
    else
    {
        if (lost)
            lostWindow->handleEvents(event);
        if (paused)
            pauseWindow->handleEvents(event);
        if (saved)
            savesScene->handleEvents(event);
    }
}

void mainScene::update(int cycle, double deltaTime)
{
    if (lost || paused)
    {
        gameBlocks.Blocklist.SaveLoadHighscore();
    }
    if (lost)
    {
        lostWindow->update(cycle, deltaTime);
        return;
    }
    if (paused)
    {
        pauseWindow->update(cycle, deltaTime);
        return;
    }
    if (saved)
    {
        savesScene->update(cycle, deltaTime);
        return;
    }
    Block *Theblock = gameBlocks.NextBlock;
    if (cycle % 2 == 0)
    {
        Theblock->autoMove(300, deltaTime);
    }
    if (!Theblock->getMovable())
    {
        spawnBlock();
    }
}
void mainScene::spawnBlock()
{
    if (gameBlocks.Blocklist.getSize() == gameBlocks.Blocklist.getmaxSize())
    {
        UsedShift = true;
        lostGame();
        return;
    }
    else
    {
        UsedShift = false;
    }
    BlockType type = static_cast<BlockType>(rand() % 3);
    BlockColor color = static_cast<BlockColor>(rand() % 3);
    gameBlocks.NextBlock = new Block(type, color, POSINIT, -32, 16, 16, renderer);
    BlocksUsed++;
}
void mainScene::render()
{
    renderer->clear();
    if (saved)
    {
        savesScene->render();
        return;
    }
    SceneMap->render(renderer, (textureSize){9, 6});
    std::string scoreStr = "Score: " + std::to_string(gameBlocks.Blocklist.getScore());

    const char *Score = scoreStr.c_str();

    renderer->renderText(Score, score, (SDL_Color){255, 255, 255, 255}, 170, 75, 50, 150);
    renderer->render(&ui.LeftArrow);
    renderer->render(&ui.RightArrow);

    gameBlocks.Blocklist.render(renderer);

    gameBlocks.NextBlock->render(renderer);
    if (lost)
    {
        lostWindow->render();
    }
    if (paused)
    {
        pauseWindow->render();
    }
    renderer->display();
}
void mainScene::restart()
{

    spawnBlock();
    gameBlocks.NextBlock->blockReset();
    gameBlocks.Blocklist.deleteList();

    BlocksUsed = 0;
    gameBlocks.Blocklist.setScore(0);
    lost = false;
}
void mainScene::handleEventsArrowsUp(SDL_Event event)
{
    switch (event.key.keysym.sym)
    {
    case SDLK_LEFT:
        ui.LeftArrow.setTexture(ui.left);
        break;
    case SDLK_RIGHT:
        ui.RightArrow.setTexture(ui.right);
        break;
    case SDLK_m:
        lostGame();
        break;
    }
}
void mainScene::lostGame()
{
    const char *score = std::to_string(gameBlocks.Blocklist.getScore()).c_str();

    lostWindow->setScore(score);

    lost = true;
}
youLostwindow *mainScene::getLostWindow()
{

    return lostWindow;
}
pause *mainScene::getPauseWindow()
{
    return pauseWindow;
}
void mainScene::pauseGame()
{
    paused = true;
}
BlocksList *mainScene::getBlocksList()
{
    return &gameBlocks.Blocklist;
}
SavesScene *mainScene::getSavesScene()
{
    return savesScene;
}

void mainScene::setSaved(bool saved)
{
    this->saved = saved;
}