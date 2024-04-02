#pragma once
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

class Vector2D
{
private:
    float x, y;

public:
    Vector2D(float x, float y);
    Vector2D() : x(0), y(0) {}
    Vector2D operator+(Vector2D v2);
    Vector2D operator-(Vector2D v2);
    Vector2D operator*(float scalar);
    Vector2D rotateVectore(int angle);
    float getX();
    float getY();
    void setX(float x);
    void setY(float y);
};