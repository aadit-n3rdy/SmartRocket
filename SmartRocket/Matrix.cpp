#include "Matrix.h"

Matrix::Matrix(unsigned int rows, unsigned int cols, double val)
{
    mat = vector<vector<double>>(rows, vector<double>(cols, val));
}

Matrix::Matrix(unsigned int rows, unsigned int cols, double* vals) {
    mat = vector<vector<double>>(rows, vector<double>(cols, 0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mat[i][j] = vals[i*cols + j];
        }
    }
}

Matrix::Matrix(unsigned int rows, unsigned int cols)
{
    srand(time(NULL));
    mat = vector<vector<double>>(rows, vector<double>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mat[i][j] = rand();
        }
    }
}

Matrix::Matrix() {
    
}

double* Matrix::operator()(unsigned int row, unsigned int col)
{
    if (row < rows() && col < cols()) {
        return &mat[row][col];
    }
    else {
        throw MatrixSizeException();
    }
}

Matrix Matrix::operator+(Matrix rhs)
{
    if (rhs.cols() != cols() || rhs.rows() != rows()) {
        throw MatrixSizeException();
    }
    Matrix returnMatrix(rows(), cols(), (double)0);
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < cols(); j++) {
            *returnMatrix(i, j) = mat[i][j] + *rhs(i, j);
        }
    }    
    return returnMatrix;
}

Matrix Matrix::operator-(Matrix rhs)
{
    if (rhs.cols() != cols() || rhs.rows() != rows()) {
        throw MatrixSizeException();
    }
    Matrix returnMatrix(rows(), cols(),(double)0);
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < cols(); j++) {
            *returnMatrix(i, j) = mat[i][j] - *rhs(i, j);
        }
    }
    return returnMatrix;
}

Matrix Matrix::operator*(Matrix rhs)
{
    if (rhs.rows() != cols()) {
        throw MatrixSizeException();
    }
    Matrix returnMatrix(rows(), rhs.cols(), 0.0);
    for (int i = 0; i < returnMatrix.rows(); i++) {
        for (int j = 0; j < returnMatrix.cols(); j++) {
            double sum = 0;
            for (int k = 0; k < cols(); k++) {
                sum += mat[i][k] * *rhs(k, j);
            }
            *returnMatrix(i, j) = sum;
        }
    }
    return returnMatrix;
}

int Matrix::rows()
{
    return mat.size();
}

int Matrix::cols()
{
    return mat[0].size();
}

void Matrix::append(bool rowWise, Matrix& rhs)
{
    if (rowWise) {
        if (rows() != rhs.rows()) {
            throw MatrixSizeException();
        }
        for (int i = 0; i < rows(); i++) {
            for (int j = 0; j < rhs.cols(); j++) {
                mat[i].push_back(*rhs(i, j));
            }
        }
    }
    else {
        if (cols() != rhs.cols()) {
            throw MatrixSizeException();
        }
        for (int i = 0; i < rhs.rows(); i++) {
            mat.push_back(rhs.toVec()[i]);
        }
    }
}

void Matrix::applyFunc(double (*func)(double inp))
{
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < cols(); j++) {
            mat[i][j] = (*func)(mat[i][j]);
        }
    }
}

vector<vector<double>> Matrix::toVec()
{
    return mat;
}
