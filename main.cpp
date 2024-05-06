#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.hpp"
using namespace std;

int WinMain()
{
    srand(time(NULL));

    game game("game with no name");
    Uint32 framesStart;
    double maxDeltaTime = 0.05f;
    double deltaTime = 0.0f;
    Uint32 lastFrameTime = SDL_GetTicks();

    while (game.getRunning())
    {
        framesStart = SDL_GetTicks();
        int frameTime;

        game.handleEvents();

        Uint32 currentFrameTime = SDL_GetTicks();
        deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f;
        if (deltaTime > maxDeltaTime)
            deltaTime = maxDeltaTime;
        lastFrameTime = currentFrameTime;

        game.update(deltaTime);
        game.render();

        frameTime = SDL_GetTicks() - framesStart;

        if (FRAMEDELAY > frameTime)
        {
            SDL_Delay(FRAMEDELAY - frameTime);
        }
    }

    SDL_Quit();
    return 0;
}
