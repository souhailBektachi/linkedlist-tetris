#include "Entity.hpp"

Entity::Entity(float x, float y, SDL_Texture *texture, float h, float w)
{
    position = Vector2D(x, y);
    this->texture = texture;
    srcRect = {0, 0, (int)w, (int)h};
    destRect = {0, 0, (int)w, (int)h};
    RenderState = renderState::Normal;
}
Entity::Entity()
{
    position = Vector2D(0, 0);
    srcRect = {0, 0, 0, 0};
    destRect = {0, 0, 0, 0};
    texture = NULL;
    RenderState = renderState::Normal;
}
Entity::~Entity()
{
}
Vector2D Entity::getPosition()
{
    return position;
}
void Entity::setPosition(Vector2D p_position)
{
    position = p_position;
    destRect.x = p_position.getX();
    destRect.y = p_position.getY();
}
void Entity::setTexture(SDL_Texture *p_texture)
{
    texture = p_texture;
}
void Entity::setSrcRect(SDL_Rect p_srcRect)
{
    srcRect = p_srcRect;
}
void Entity::setDestRect(SDL_Rect p_destRect)
{
    destRect = p_destRect;
}
void Entity::setRenderState(renderState state)
{
    RenderState = state;
}
SDL_Rect Entity::getSrcRect()
{
    return srcRect;
}
SDL_Rect Entity::getDestRect()
{
    return destRect;
}
SDL_Texture *Entity::getTexture()
{
    return texture;
}
renderState Entity::getRenderState()
{
    return RenderState;
}
void Entity::cleanup()
{
    SDL_DestroyTexture(texture);
}