#pragma once
#include "Entity.hpp"
#include "renderWindow.hpp"
#include <iostream>
#include "enums.hpp"

class Block : public Entity
{
private:
    BlockType type;
    BlockColor color;
    bool Movable;
    bool Destroyed;
    static int max[2];

public:
    Block(BlockType p_type, BlockColor p_color, float x, float y, float w, float h, RenderWindow *window);
    Block();
    ~Block();
    void render(RenderWindow *window);
    bool move(KeyPos Pos);
    void input(double DT);
    void autoMove(int speed, double DT);
    BlockType getType();
    BlockColor getColor();
    bool getMovable();
    bool getDestroyed();
    void setDestroyed(bool p_destroyed);
    void setMovable(bool p_movable);
    void setType(BlockType p_type);
    void setColor(BlockColor p_color);
    void blockReset();
    void static decreaseMax(Inserted pos);
    void getTexture(BlockType type, BlockColor color, RenderWindow *window);
};