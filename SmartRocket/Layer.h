#pragma once

#include <cmath>
#include <random>
#include <exception>
#include "Matrix.h"

double sigmoid(double z);
double sigmoidPrime(double z);

struct BadInputException : public std::exception {
	const char* what() const throw() {
		return "Bad Input";
	}
};

class Layer {
private:
	Matrix wt;
	Matrix da;
	Matrix a;
	Matrix z;
	int inCount;
	int outCount;
	double learningRate;
	void biasAdjust();

public:
	Layer(int inWoB, int outWoB, double eta);
	int getOutCount();
	int getInCount();
	double getDa(int index);
	double getZ(int index);
	double getA(int index);
	Matrix getWt();
	void setWt(Matrix weight);
	void calc(Layer input);
	void calc(Matrix input);
	void calcDerivativeFinal(Matrix ideal);
	void calcDerivativeHidden(Layer nextLayer);
	void weightAdjust(Layer prevLayer);
	void weightAdjust(Matrix prevLayer);
};
