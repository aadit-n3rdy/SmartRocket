#pragma once
#include "Vec2.h"
class Obstacle {
private:
	Vec2 pos;
	float radius;
public:
	Vec2 getPos();
	void setPos(Vec2 newPos);

	float getRadius();
	void setRadius(float newradius);
};
