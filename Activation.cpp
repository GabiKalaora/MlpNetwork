#include "Activation.h"
#include <cmath>

using std::exp;
using std::cout;
using std::endl;
using std::cerr;


/**
 * ctor for Activation class
 * @param activationType
 */
Activation:: Activation(ActivationType toActivate)
{
    if (toActivate != Relu && toActivate !=  Softmax)
    {
        cerr << "activation func should be Relu or Softmax." << endl;
        exit(EXIT_FAILURE);
    }
    this->_activationFunc = toActivate;
}

/**
 * getter method for _activationType field
 * @return type of func wanted
 */
ActivationType Activation::getActivationType() const
{
    return this->_activationFunc;
}

/**
 * applies appropriate func on given matrix
 * @param mat to apply fuc on
 * @return a new matrix after applying chosen func
 */
Matrix Activation::operator()(Matrix &mat)
{
    Matrix newMatrix(mat);
    if (this->_activationFunc == Relu)
    {
        newMatrix = _reluFunc(mat);
    }
    else if (this->_activationFunc == Softmax)
    {
        newMatrix = _softmaxFunc(mat);
    }
    return newMatrix;
}

/**
 * Relu func
 * @param mat to applay Relu fun on
 * @return a new func after applied Relu func on matrix
 */
Matrix Activation::_reluFunc(Matrix &m)
{
    Matrix newMatrix;
    newMatrix = m;
    for (int q = 0; q < m.getRows() * m.getCols(); q++)
    {
        if (newMatrix[q] < 0)
        {
            newMatrix[q] = 0;
        }
    }
    return newMatrix;
}

/**
 * Softmax func
 * @param mat to applay Softmax fun on
 * @return a new func after applied Softmax func on matrix
 */
Matrix Activation::_softmaxFunc(Matrix &m)
{
    Matrix newMatrix;
    newMatrix = m;
    float sumOfExpOnVecElements = 0;
    for (int q = 0; q < m.getRows() * m.getCols(); q++)
    {
        sumOfExpOnVecElements += exp(newMatrix[q]);
    }

    for (int i = 0; i < m.getRows() * m.getCols(); i++)
    {
        float tempVal = m[i];
        newMatrix[i] = exp(tempVal) * (1 / sumOfExpOnVecElements);
    }
    return newMatrix;
}

