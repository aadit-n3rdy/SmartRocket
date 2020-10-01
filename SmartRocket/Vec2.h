#pragma once
#include <cmath>

class Vec2
{
public:
	double x;
	double y;
	double dist(Vec2 other);
	Vec2(double xVal, double yVal);
	Vec2();
	Vec2 operator + (Vec2 rhs);
	Vec2 operator * (double rhs);
};

