#include "Rocket.h"

inline Rocket::Rocket(Vec2 position, Rocket parent, Obstacle obstacle, Target targetParam) {
    pos = position;
    target = targetParam;
    ptron = Perceptron(std::vector<int>{8, 6, 6, 2}, parent.getPtron().getEta());
    ptron.setLayers(parent.getPtron().getLayers());
    obs = obstacle;
    for (Layer layer : ptron.getLayers()) {
        Matrix wt = layer.getWt();
        wt.applyFunc(randomAdjust);
        layer.setWt(wt);
    }
}

inline Rocket::Rocket(Vec2 position, Obstacle obstacle, Target targetParam) {
    target = targetParam;
    pos = position;
    obs = obstacle;
    ptron = Perceptron(std::vector<int>{8, 6, 6, 2}, eta);
}

inline Vec2 Rocket::getPosition() {
    return pos;
}

inline Perceptron Rocket::getPtron() {
    return ptron;
}

inline RocketState Rocket::getState() {
    return state;
}

inline void Rocket::update(float deltaTime) {
    Vec2 obsRel = obs.getPos().sub(pos);
    Vec2 targetRel = target.getPos() + pos * -1;
    double input[] = { obsRel.x, obsRel.y, targetRel.x, targetRel.y, pos.x, pos.y, vel.x, vel.y };
    ptron.calc(Matrix(8, 1, (double*)input));
    Vec2 accel = Vec2(ptron.getLayers()[ptron.getLayers().size() - 1].getZ(0)
        , ptron.getLayers()[ptron.getLayers().size() - 1].getZ(1));
    accel = accel * forceFactor;
    vel = vel + (accel * deltaTime * velFactor);
    pos = pos + (vel * deltaTime);

    if ((pos.dist(obs.getPos()) < obs.getRadius())) {
        state = RocketState::DEAD;
    }
    //TODO check if rocket is out of bounds
    else if (pos.dist(target.getPos()) < target.getRadius()) {
        state = RocketState::DONE;
    }
}

inline void Rocket::draw() {
    if (state == RocketState::ALIVE) {
        //TODO set color blue

    }
    else if (state == RocketState::DONE) {
        //TODO set color green

    }
    else {
        //TODO set color red

    }
    //TODO draw circle
}

double randomAdjust(double inp)
{
    return inp + ((double)(rand()%100)) * 0.5;
}
