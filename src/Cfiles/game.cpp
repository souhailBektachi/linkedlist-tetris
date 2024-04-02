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
        renderer = new RenderWindow(title, SCREEN_WIDTH, SCREEN_HEIGHT);

        isRunning = true;
    }
    gameState = Playing;
    deltaTime = 0.0f;
    changeScene(gameState);
}
game::~game()
{
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

        default:
            break;
        }
        ((mainScene *)Scene)->handleEvents(event);
    }
}
void game::changeScene(GameState state)
{
    switch (state)
    {
    case Playing:
        Scene = (void *)new mainScene(&renderer);
        break;

    default:
        break;
    }
}
void game::render()
{
    ((mainScene *)Scene)->render();
}
void game::update(double deltaTime)
{
    static int cycle = 0;

    cycle++;
    ((mainScene *)Scene)->update(cycle, deltaTime);
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