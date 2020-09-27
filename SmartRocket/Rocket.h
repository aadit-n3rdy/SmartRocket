#pragma once

#include "ofMain.h"
#include "Perceptron.h"
#include "ofApp.h"
#include "ofVec2f.h"

enum RocketState {
    ALIVE,
    DEAD,
    DONE
};

class Rocket {
private:
    Perceptron ptron;
    ofVec2f pos;
    ofVec2f vel;
    RocketState state = RocketState::ALIVE;
    const static double velFactor = 1.0;
    const static double forceFactor = 2000.0;
    const static double eta = 0.5;
    Obstacle obs;
    Target target;

    public Rocket(PVector position, Rocket parent, Obstacle obstacle, Target targetParam) {
        pos = position;
        target = targetParam;
        ptron = new Perceptron(new int[] {8, 6, 6, 2}, parent.getPtron().getEta());
        ptron.setLayers((ArrayList<Layer>)parent.getPtron().getLayers().clone());
        obs = obstacle;
        for (Layer layer : ptron.getLayers()) {
            SimpleMatrix wt = layer.getWt();
            for (DMatrixIterator it = wt.iterator(true, 0, 0, wt.numRows() - 1, wt.numCols() - 1); it.hasNext(); ) {
                double val = it.next();
                it.set(val + (5 - Math.random() * 10));
            }
            layer.setWt(wt);
        }
    }

    public Rocket(PVector position, Obstacle obstacle, Target targetParam) {
        target = targetParam;
        pos = position;
        obs = obstacle;
        int[] shape = { 8, 6, 6, 2 };
        ptron = new Perceptron(shape, eta);
    }

    public PVector getPosition() {
        return pos;
    }

    public Perceptron getPtron() {
        return ptron;
    }

    public void update(float deltaTime) {
        PVector obsRel = obs.getPos().sub(pos);
        PVector targetRel = target.getPosition().sub(pos);
        double[][] input = { {obsRel.x}, {obsRel.y}, {targetRel.x}, {targetRel.y}, {pos.x}, {pos.y}, {vel.x}, {vel.y} };
        ptron.calc(new SimpleMatrix(input));
        PVector accel = new PVector((float)ptron.getLayers().get(ptron.getLayers().size() - 1).getZ(0)
            , (float)ptron.getLayers().get(ptron.getLayers().size() - 1).getZ(1));
        accel = accel.mult((float)forceFactor);
        vel.add(accel.mult((float)(deltaTime * velFactor)));
        vel.setMag((vel.mag() > 100) ? 100 : vel.mag());
        pos = pos.add(vel.mult(deltaTime));

        if ((pos.dist(obs.getPos()) < obs.getRadius())) {
            state = RocketState.DEAD;
        }
        else if (pos.x > PtronApplet.width || pos.x < 0) {
            state = RocketState.DEAD;
        }
        else if (pos.y > PtronApplet.height || pos.y < 0) {
            state = RocketState.DEAD;
        }
        else if (pos.dist(Target.getPosition()) < Target.getRadius()) {
            state = RocketState.DONE;
        }
    }

    public void draw(PApplet applet) {
        if (state == RocketState.ALIVE) {
            applet.fill(0, 0, 255);

        }
        else if (state == RocketState.DONE) {
            applet.fill(0, 255, 0);

        }
        else {
            applet.fill(255, 0, 0);

        }
        applet.ellipse(pos.x, pos.y, 25, 25);
    }

    public RocketState getState() {
        return state;
    }

}

