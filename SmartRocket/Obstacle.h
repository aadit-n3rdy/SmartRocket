#pragma once
#include "ofVec2f"
class Obstacle {
private:
	ofVec2f pos;
	float radius;
public:
	ofVec2f getPos() {
		return pos;
	}
	void setPos(ofVec2f newPos) {
		pos = newPos;
	}

	float getRadius() {
		return radius;
	}
	void setRadius(float newradius) {
		radius = newradius;
	}
}
