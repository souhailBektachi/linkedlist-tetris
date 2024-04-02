#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.hpp"
using namespace std;
int UpdateAndRender(void *data)
{
    Uint32 framesStart;
    double deltaTime = 0.0f;
    double maxDeltaTime = 0.05f;
    Uint32 lastFrameTime = SDL_GetTicks();
    game *mygame = (game *)data;
    while (mygame->getRunning())
    {
        framesStart = SDL_GetTicks();
        int frameTime;
        // mygame->handleEvents();
        mygame->update(deltaTime);
        mygame->render();
        frameTime = SDL_GetTicks() - framesStart;
        Uint32 currentFrameTime = SDL_GetTicks();
        deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f;
        if (deltaTime > maxDeltaTime)
            deltaTime = maxDeltaTime;
        lastFrameTime = currentFrameTime;
        // printf("deltaTime:%f\n", deltaTime);

        if (FRAMEDELAY > frameTime)
        {
            SDL_Delay(FRAMEDELAY - frameTime);
        }
    }
    return 0;
}
int WinMain()
{
    srand(time(NULL));
    game game("game with no name");
    SDL_Thread *updateThread = SDL_CreateThread(UpdateAndRender, "UpdateAndRender", (void *)&game);

    while (game.getRunning())
    {
        game.handleEvents();

        SDL_Delay(FRAMEDELAY);
    }
    SDL_WaitThread(updateThread, NULL);

    SDL_Quit();
    return 0;
}