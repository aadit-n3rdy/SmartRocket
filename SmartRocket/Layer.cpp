#include "Layer.h"
#include "Layer.h"

double sigmoid(double z)
{
	return 1 / (1 + std::exp(z));
}

double sigmoidPrime(double z)
{
	return sigmoid(z) * (1 - sigmoid(z));
}

void Layer::biasAdjust() {
	double dw;
	for (int i = 0; i < wt.rows(); i++) {
		dw = *da(i, 0) * sigmoidPrime(*z(i, 0));
		*wt(i, wt.cols() - 1) = *wt(i, wt.cols() - 1) - (learningRate * dw);
		
	}
}

Layer::Layer(int inWoB, int outWoB, double eta) {
	inCount = inWoB;
	outCount = outWoB;
	wt = Matrix(outCount, inWoB + 1);
	a = Matrix(outCount, 1);
	z = Matrix(outCount, 1);
	da = Matrix(outCount, 1);
	learningRate = eta;
}

inline int Layer::getOutCount()
{
	return outCount;
}

inline int Layer::getInCount() {
	return inCount;
}

inline double Layer::getDa(int index)
{
	return *da(index, 0);
}

inline double Layer::getZ(int index)
{
	return *z(index, 0);
}

inline double Layer::getA(int index)
{
	return *a(index, 0);
}

inline Matrix Layer::getWt() { return wt; }

inline void Layer::setWt(Matrix weight) { wt = weight; }

inline void Layer::calc(Layer input)
{
	calc(input.a);
}

inline void Layer::calc(Matrix input)
{
	if (input.rows() != inCount || input.cols() != 1)
	{
		throw BadInputException();
	}
	Matrix temp(1, 1);
	*temp(0, 0) = 1.0;
	Matrix inpmat(input.rows() + 1, input.cols());
	inpmat.append(false, temp);
	z = wt * inpmat;
	a = z;
	a.applyFunc(sigmoid);
}

inline void Layer::calcDerivativeFinal(Matrix ideal) {
	if (ideal.rows() != outCount) {
		throw BadInputException();
	}
	for (int i = 0; i < da.rows(); i++) {
		*da(i, 0) = *ideal(i, 0) - 1;
	}
}

inline void Layer::calcDerivativeHidden(Layer nextLayer) {
	if (nextLayer.getInCount() != inCount) {
		throw BadInputException();
	}
	for (int i = 0; i < a.rows(); i++) {
		*da(i, 0) = 0;
		for (int j = 0; j < nextLayer.outCount; j++)
		{
			*da(i, 0) += *nextLayer.wt(j, i) * sigmoidPrime(nextLayer.getZ(j)) * nextLayer.getDa(j);
		}
	}
}

inline void Layer::weightAdjust(Layer prevLayer) {
	weightAdjust(prevLayer.a);
}

inline void Layer::weightAdjust(Matrix prevLayer) {
	if (prevLayer.rows() != inCount) {
		throw BadInputException();
	}
	double dw;
	for (int i = 0; i < prevLayer.rows(); i++) {
		dw = 0;
		for (int j = 0; j < da.rows(); j++) {
			dw = *da(j, 0) * sigmoidPrime(*z(j, 0) * *prevLayer(i, 0));
			*wt(j, i) = *wt(j, i) - (dw * learningRate);
		}
	}
	biasAdjust();
}