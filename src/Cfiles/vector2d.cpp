#include "vector2d.hpp"
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
Vector2D::Vector2D(float x, float y)
{
    this->x = x;
    this->y = y;
}
Vector2D Vector2D::operator+(Vector2D v2)
{
    Vector2D res;
    res.x = x + v2.x;
    res.y = y + v2.y;
    return res;
}
Vector2D Vector2D::operator-(Vector2D v2)
{
    Vector2D res;
    res.x = x - v2.x;
    res.y = y - v2.y;
    return res;
}
Vector2D Vector2D::operator*(float scalar)
{
    Vector2D res;
    res.x = x * scalar;
    res.y = y * scalar;
    return res;
}
Vector2D Vector2D::rotateVectore(int angle)
{
    Vector2D res;
    res.x = cos(angle) * x - sin(angle) * y;
    res.y = sin(angle) * x * cos(angle) * y;
    return res;
}

float Vector2D::getX()
{
    return x;
}
float Vector2D::getY()
{
    return y;
}
void Vector2D::setX(float x)
{
    this->x = x;
}
void Vector2D::setY(float y)
{
    this->y = y;
}