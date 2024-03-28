#pragma once

enum renderState
{
    Fliped,
    Normal
};

enum KeyPos
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};
enum Inserted
{
    left,
    right
};
enum BlockType
{
    Circle,
    Square,
    Triangle,
    Hexagon,

};
enum BlockColor
{
    Red,
    Green,
    Blue,
    Yellow,

};
enum MevementState
{
    Auto,
    Manual
};
enum Insertion
{
    Head,
    Tail
};
// Game enums
typedef enum GameState
{
    Playing,
    GameOver,
    GameWon,
    Paused
};