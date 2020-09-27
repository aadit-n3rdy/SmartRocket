#pragma once
#include <vector>
using namespace std;

struct MatrixSizeException : public exception {
	const char* what() const throw() {
		return "Matrix of invalid size passed";
	}
};

class Matrix
{
private:
	vector<vector<double>> mat;
public:
	Matrix(unsigned int rows, unsigned int cols, double val);

	vector<double> operator [](int row);
	Matrix operator +(Matrix rhs);
	Matrix operator -(Matrix rhs);
	Matrix operator *(Matrix rhs);

	int rows();
	int cols();
	void append(bool rowWise, Matrix& toBeAppended);
	void applyFunc(double (*func)(double inp));
	vector<vector<double>> toVec();
};

