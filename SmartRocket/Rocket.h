#pragma once

#include "Perceptron.h"
#include "Obstacle.h"
#include "Target.h"
#include "Vec2.h"
#include <vector>

enum RocketState {
    ALIVE,
    DEAD,
    DONE
};

double randomAdjust(double inp);

class Rocket {
private:
    Perceptron ptron;
    Vec2 pos;
    Vec2 vel;
    RocketState state = RocketState::ALIVE;
    double velFactor = 1.0;
    double forceFactor = 2000.0;
    double eta = 0.5;
    Obstacle obs;
    Target target;

public:
    Rocket(Vec2 position, Rocket parent, Obstacle obstacle, Target targetParam);

    Rocket(Vec2 position, Obstacle obstacle, Target targetParam);

    Vec2 getPosition();

    Perceptron getPtron();

    void update(float deltaTime);
    void draw();
    inline RocketState getState();
};
