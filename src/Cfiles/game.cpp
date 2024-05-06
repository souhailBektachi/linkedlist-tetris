#include "game.hpp"

game::game(const char *title)
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        printf("SDL INIT HAS FAILED %s", SDL_GetError());
        isRunning = false;
    }
    else
    {
        if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
        {
            fprintf(stderr, "Unable to initialize SDL_image: %s\n", IMG_GetError());
        }
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
        if (TTF_Init() == -1)
        {
            printf("TTF_Init: %s\n", TTF_GetError());
        }
        renderer = new RenderWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT);

        isRunning = true;
    }
    gameState = MainMenu;
    deltaTime = 0.0f;
    scenes.menu = nullptr;
    scenes.mainGame = nullptr;
    Scene = nullptr;
    icon::loadTex(renderer);
    changeScene(gameState);
}
game::~game()
{
    TTF_Quit();
}
void game::handleEvents()
{

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {

            case SDLK_p:
                if (gameState == Playing)
                    scenes.mainGame->paused = !scenes.mainGame->paused;
                break;
            }

        default:
            break;
        }
        switch (gameState)
        {
        case MainMenu:
            ((Menu *)Scene)->handleEvents(event);
            break;
        case Playing:
            ((mainScene *)Scene)->handleEvents(event);
            break;
        case Exit:
            isRunning = false;
            break;
        default:
            break;
        }
    }
    handleButtonsEvents();
}
void game::changeScene(GameState state)
{
    Scene = nullptr;
    switch (state)
    {
    case Playing:
        if (scenes.mainGame == nullptr)
        {
            scenes.mainGame = new mainScene(&renderer);
        }

        Scene = (void *)scenes.mainGame;

        break;
    case MainMenu:
        if (scenes.menu == nullptr)
        {
            scenes.menu = new Menu(&renderer);
        }

        Scene = (void *)scenes.menu;

        break;
    default:
        break;
    }
}
void game::render()
{
    if (Scene == nullptr)
        return;
    switch (gameState)
    {
    case MainMenu:
        ((Menu *)Scene)->render();
        break;
    case Playing:
        ((mainScene *)Scene)->render();

        break;

    default:
        break;
    }
}
void game::update(double deltaTime)
{
    if (Scene == nullptr)
        return;
    static int cycle = 0;
    if (Scene == nullptr)
        return;

    cycle++;
    switch (gameState)
    {
    case MainMenu:
        ((Menu *)Scene)->update(cycle, deltaTime);
        break;
    case Playing:
        ((mainScene *)Scene)->update(cycle, deltaTime);
        break;
    default:

        break;
    }

    if (cycle == 120)
    {
        cycle = 0;
    }
    this->deltaTime = deltaTime;
}
void game::resetGame()
{

    changeScene(Playing);
}

bool game::getRunning()
{
    return isRunning;
}
void game::handleButtonsEvents()
{
    switch (gameState)
    {
    case MainMenu:
        gameState = ((Menu *)Scene)->buttonsEvents();
        changeScene(gameState);

        break;
    case Playing:
        if (!scenes.mainGame->lost && !scenes.mainGame->paused)
        {
            break;
        }
        if (scenes.mainGame->lost)
        {
            handlLostEvents();
        }
        else if (scenes.mainGame->paused)
        {
            handlePauseEvents();
        }

        break;
    default:
        break;
    }
}
void game::handlLostEvents()
{
    if (scenes.mainGame->getLostWindow()->getHome()->getClicked())
    {
        delete scenes.mainGame;
        scenes.mainGame = nullptr;
        gameState = MainMenu;
        SDL_Delay(100);
        changeScene(gameState);
    }
    else if (scenes.mainGame->getLostWindow()->getRestart()->getClicked())
    {
        ((mainScene *)Scene)->restart();
        ((mainScene *)Scene)->getLostWindow()->getRestart()->setClicked(false);
    }
}
void game::handlePauseEvents()
{
    if (scenes.mainGame->getPauseWindow()->getHome()->getClicked())
    {
        delete scenes.mainGame;
        scenes.mainGame = nullptr;
        gameState = MainMenu;
        SDL_Delay(100);
        changeScene(gameState);
    }
    else if (scenes.mainGame->getPauseWindow()->getRestart()->getClicked())
    {
        ((mainScene *)Scene)->restart();
        ((mainScene *)Scene)->getPauseWindow()->getRestart()->setClicked(false);
        scenes.mainGame->paused = false;
    }
    else if (scenes.mainGame->getPauseWindow()->getPlay()->getClicked())
    {
        scenes.mainGame->paused = false;
        scenes.mainGame->getPauseWindow()->getPlay()->setClicked(false);
    }
}