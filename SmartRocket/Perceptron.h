#pragma once
#include <vector>
#include "Layer.h"

using namespace std;

class Perceptron {

private:
    vector<int> shape;
    double eta;
    vector<Layer> layers;

public:
    Perceptron(vector<int> shp, double learningRate);
    Perceptron();
    void setLayers(vector<Layer> parent);
    double getEta();
    void setEta(double e);
    void calc(Matrix in);
    void learn(Matrix in, Matrix expected);
    vector<Layer> getLayers();

};