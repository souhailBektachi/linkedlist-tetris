#include "block.hpp"

int Block::max[2] = {POSINIT - 32, POSINIT};

Block::Block(BlockType p_type, BlockColor p_color, int x, int y, int w, int h, RenderWindow *window) : Entity(x, y, nullptr, h, w)
{

    type = p_type;
    color = p_color;
    Destroyed = false;
    Movable = true;
    if (window != nullptr)
        getTexture(type, color);
    this->destRect.h = this->destRect.w = 32;
}
Block::Block()
{
}
Block::~Block()
{
}
void Block::render(RenderWindow *window)
{
    if (!Destroyed)
    {
        window->render(this);
    }
}

void Block::setType(BlockType type)
{
    this->type = type;
}
void Block::setColor(BlockColor color)
{
    this->color = color;
}
BlockType Block::getType()
{
    return type;
}
BlockColor Block::getColor()
{
    return color;
}
bool Block::getMovable()
{
    return Movable;
}
bool Block::getDestroyed()
{
    return Destroyed;
}
void Block::destroy()
{
    Destroyed = true;
}
void Block::getTexture(BlockType type, BlockColor color)
{
    texture = Globalcolors[type][color];
}
void Block::setMovable(bool p_movable)
{
    Movable = p_movable;
}
bool Block::move(KeyPos Pos)
{
    if (!Movable)
    {
        return false;
    }
    switch (Pos)
    {
    case LEFT:
        if (max[0] <= 0)
        {
            return false;
        }

        setPosition({(float)max[0], (float)SCREEN_HEIGHT - 64});
        max[0] -= 32;
        break;
    case RIGHT:
        if (max[1] >= SCREEN_WIDTH - 32)
        {
            return false;
        }
        setPosition({(float)max[1], (float)SCREEN_HEIGHT - 64});
        max[1] += 32;
        break;
    default:
        break;
    }
    Movable = false;
    return true;
}

void Block::autoMove(int speed, double DT)
{
    if (position.getY() >= SCREEN_HEIGHT / 2)
    {
        return;
    }

    Block Theblock;
    Theblock.setPosition({position.getX(), position.getY()});

    int y = sin(-(3 * M_PI) / 2) * DT * speed;

    if (position.getY() + y < SCREEN_HEIGHT / 2)
    {

        Theblock.setPosition({this->position.getX(), this->position.getY() + y});
    }
    else
    {
        Theblock.setPosition({position.getX(), (float)SCREEN_HEIGHT / 2});
    }

    position = {Theblock.position.getX(), Theblock.position.getY()};
}
void Block::input(double DT)
{
}
void Block::blockReset()
{
    max[0] = POSINIT - 32;
    max[1] = POSINIT;
}
void Block::decreaseMax(Inserted pos)
{
    switch (pos)
    {
    case left:
        max[0] += 32 * NUMTOMATCH;
        break;
    case right:
        max[1] -= 32 * NUMTOMATCH;
        break;
    }
}

void Block::loadTex(RenderWindow *renderer)
{
    const char *blocks[4 * 4] = {
        "assets/gfx/blocks/RedCircle.png",
        "assets/gfx/blocks/GreenCircle.png",
        "assets/gfx/blocks/BlueCircle.png",
        "assets/gfx/blocks/YellowCircle.png",
        "assets/gfx/blocks/RedBlock.png",
        "assets/gfx/blocks/GreenBlock.png",
        "assets/gfx/blocks/BlueBlock.png",
        "assets/gfx/blocks/YellowBlock.png",
        "assets/gfx/blocks/RedTriangle.png",
        "assets/gfx/blocks/GreenTriangle.png",
        "assets/gfx/blocks/BlueTriangle.png",
        "assets/gfx/blocks/YellowTriangle.png",
        "assets/gfx/blocks/RedHexagon.png",
        "assets/gfx/blocks/GreenHexagon.png",
        "assets/gfx/blocks/BlueHexagon.png",
        "assets/gfx/blocks/YellowHexagon.png",

    };
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Globalcolors[i][j] = renderer->loadTexture(blocks[i * 4 + j]);
        }
    }
    destruction = renderer->loadTexture("assets/gfx/destruction.png");
}

void Block::resetMax()
{
    max[0] = POSINIT - 32;
    max[1] = POSINIT;
}