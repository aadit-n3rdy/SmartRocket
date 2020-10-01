#include "Perceptron.h"

inline Perceptron::Perceptron(vector<int> shp, double learningRate)
{
    eta = learningRate;
    shape = shp;
    layers = std::vector<Layer>();
    for (int i = 1; i < shape.size(); i++) {
        layers.push_back(Layer(shape[i - 1], shape[i], eta));
    }
}

inline Perceptron::Perceptron()
{
    eta = 0.5;
    
}

inline void Perceptron::setLayers(vector<Layer> parent) {
    layers = parent;
}

inline double Perceptron::getEta() { return eta; }

inline void Perceptron::setEta(double e) { eta = e; }

inline void Perceptron::calc(Matrix in)
{
    if (in.rows() != shape[0] || in.cols() != 1) {
        throw BadInputException();
    }
    layers[0].calc(in);
    for (int i = 1; i < layers.size(); i++) {
        layers[i].calc(layers[i-1]);
    }
}

inline void Perceptron::learn(Matrix in, Matrix expected)
{
    if (in.rows() != shape[0] || in.cols() != 1) {
        throw BadInputException();
    }
    if (expected.rows() != shape[shape.size() - 1] || expected.cols() != 1) {
        throw BadInputException();
    }
    calc(in);
    layers.back().calcDerivativeFinal(expected);
    for (int i = 0; i < layers.size() - 1; i++) {
        layers[i].calcDerivativeHidden(layers[i+1]);
    }
    layers[0].weightAdjust(in);
}

inline vector<Layer> Perceptron::getLayers() {
    return layers;
}
