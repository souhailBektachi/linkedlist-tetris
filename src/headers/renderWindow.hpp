#pragma once
class Entity;
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "Entity.hpp"
#include "enums.hpp"
using namespace std;
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
    SDL_Renderer *getRenderer();
    TTF_Font *loadFont(const char *p_filePath, int p_size);
    void renderText(const char *p_text, TTF_Font *p_font, SDL_Color p_color, int p_x, int p_y, int h, int w);
    void renderTextWithmultipleColors(const char *p_text, TTF_Font *p_font, SDL_Color p_colors[], int p_x, int p_y);
    void destroyFont(TTF_Font *p_font);
    void ChangeFontColor(TTF_Font *p_font, SDL_Color p_color);
};
