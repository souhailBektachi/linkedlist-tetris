#include "mainGame.hpp"

mainScene::mainScene(RenderWindow **renderer)
{
    this->renderer = *renderer;
    Block::loadTex(this->renderer);

    gameBlocks.numberofBlocks = 0;
    gameBlocks.Blocklist.setmaxSize(17);
    map = "assets/maps/secondmap.csv";
    SDL_Texture *maptex = this->renderer->loadTexture("assets/gfx/Texture.png");

    SceneMap = new Map(map, maptex);

    spawnBlock();
}
mainScene::~mainScene()
{
    delete SceneMap;
}
void mainScene::handleEvents(SDL_Event event)
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
            break;
        case SDLK_RIGHT:
            if (gameBlocks.NextBlock->move(RIGHT))
            {
                gameBlocks.Blocklist.insert(gameBlocks.NextBlock);
            }
            break;
        case SDLK_r:
            restart();

            break;
        case SDLK_e:
            gameBlocks.Blocklist.shift();
            break;
        }
    }
}

void mainScene::update(int cycle, double deltaTime)
{
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
        return;
    }
    BlockType type = static_cast<BlockType>(rand() % 3);
    BlockColor color = static_cast<BlockColor>(rand() % 3);
    gameBlocks.NextBlock = new Block(type, color, POSINIT, -32, 16, 16, renderer);
}
void mainScene::render()
{
    renderer->clear();
    SceneMap->render(renderer, (textureSize){9, 6});

    gameBlocks.Blocklist.render(renderer);
    gameBlocks.NextBlock->render(renderer);
    renderer->display();
}
void mainScene::restart()
{

    spawnBlock();
    gameBlocks.NextBlock->blockReset();
    gameBlocks.Blocklist.deleteList();
}