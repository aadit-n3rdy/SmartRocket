#include "Obstacle.h"

inline Vec2 Obstacle::getPos() {
	return pos;
}

inline void Obstacle::setPos(Vec2 newPos) {
	pos = newPos;
}

inline float Obstacle::getRadius() {
	return radius;
}

inline void Obstacle::setRadius(float newradius) {
	radius = newradius;
}
