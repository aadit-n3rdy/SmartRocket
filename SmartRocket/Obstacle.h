#pragma once
#include "Vec2.h"
class Obstacle {
private:
	Vec2 pos;
	float radius;
public:
	Vec2 getPos() {
		return pos;
	}
	void setPos(Vec2 newPos) {
		pos = newPos;
	}

	float getRadius() {
		return radius;
	}
	void setRadius(float newradius) {
		radius = newradius;
	}
};
