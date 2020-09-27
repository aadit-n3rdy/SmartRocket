#pragma once
#include <vector>
using namespace std;

struct MatrixSizeException : public exception {
	const char* what() const throw() {
		return "Matrix of invalid size passed";
	}
};

struct MatrixIndex {
	int row;
	int col;
};

class Matrix
{
private:
	vector<vector<double>> mat;
public:
	Matrix(unsigned int rows, unsigned int cols, double val);
	Matrix(unsigned int rows, unsigned int cols, double* vals);

	double* operator()(unsigned int row, unsigned int col);
	Matrix operator +(Matrix rhs);
	Matrix operator -(Matrix rhs);
	Matrix operator *(Matrix rhs);

	int rows();
	int cols();
	void append(bool rowWise, Matrix& toBeAppended);
	void applyFunc(double (*func)(double inp));
	vector<vector<double>> toVec();
};

