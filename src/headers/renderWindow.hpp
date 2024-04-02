#pragma once
class Entity;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "Entity.hpp"
#include "enums.hpp"
class RenderWindow
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;

public:
    RenderWindow(const char *p_title, int p_w, int p_h);
    RenderWindow();
    ~RenderWindow();
    SDL_Texture *loadTexture(const char *p_filePath);
    static SDL_Texture *TextureLoader(const char *p_filePath);
    void render(Entity *p_entity);
    void clear();
    void rendernewcolor();
    void display();
};
