#include "Target.h"

Vec2 Target::getPos()
{
    return pos;
}

double Target::getRadius()
{
    return radius;
}

Target::Target(double x, double y, double rad)
{
    pos = Vec2(x, y);
    radius = rad;
}
