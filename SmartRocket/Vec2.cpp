#include "Vec2.h"

double Vec2::dist(Vec2 other)
{
	double dx = other.x - x;
	double dy = other.y - y;
	return sqrt(dx * dx + dy * dy);
}

Vec2::Vec2(double xVal, double yVal)
{
	x = xVal;
	y = yVal;
}

Vec2::Vec2() {
	x = 0;
	y = 0;
}

Vec2 Vec2::operator+(Vec2 rhs)
{
	return Vec2(rhs.x + x, rhs.y + y);
}

Vec2 Vec2::operator*(double rhs)
{
	return Vec2(rhs * x, rhs * y);
}
