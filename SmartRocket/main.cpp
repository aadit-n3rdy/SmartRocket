#include <iostream>
#include "Matrix.h"

void printMatrix(Matrix& m) {
	for (int i = 0; i < m.rows(); i++) {
		for (int j = 0; j < m.cols(); j++) {
			std::cout << *m(i, j) << " ";
		}
		std::cout << std::endl;
	}
}

int main() {
	double datam1[3] = { 0.5, 1.0, 2.5 };
	double datam2[3] = { 1.0, 0.0, 0.0};
	Matrix m1(3, 1, (double*)datam1);
	Matrix m2(3, 1, (double*)datam2);
	
	m2.append(false, m1);
	printMatrix(m1);
	std::cout << std::endl;
	printMatrix(m2);
	std::cout << std::endl;
	return 0;
}