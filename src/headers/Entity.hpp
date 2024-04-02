#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include "vector2d.hpp"
#include "csts.hpp"
#include "enums.hpp"

typedef struct
{
    int h;
    int w;
} textureSize;

class Entity
{
protected:
    SDL_Rect srcRect;
    SDL_Rect destRect;
    Vector2D position;
    SDL_Texture *texture;
    renderState RenderState;

public:
    Entity(float x, float y, SDL_Texture *texture, float h, float w);
    Entity();
    ~Entity();
    Vector2D getPosition();
    void setPosition(Vector2D p_position);
    void setTexture(SDL_Texture *p_texture);
    void setSrcRect(SDL_Rect p_srcRect);
    void setDestRect(SDL_Rect p_destRect);
    void setRenderState(renderState state);
    SDL_Rect getSrcRect();
    SDL_Rect getDestRect();
    SDL_Texture *getTexture();
    renderState getRenderState();
    void cleanup();
};