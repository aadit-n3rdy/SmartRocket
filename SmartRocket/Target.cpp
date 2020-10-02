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

Target::Target()
{
    pos = Vec2(0, 0);
    radius = 0;
}
