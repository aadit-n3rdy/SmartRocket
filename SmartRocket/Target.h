#pragma once
#include "Vec2.h"
class Target
{
private:
	Vec2 pos;
	double radius;
public:
	Vec2 getPos();
	double getRadius();
	Target(double x, double y, double rad);
};

