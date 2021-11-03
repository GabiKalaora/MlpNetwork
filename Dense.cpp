#include "Activation.h"
#include "Dense.h"

/**
 * Dense ctor
 * @param w gets a weight matrix
 * @param bias gets a cias matrix
 * @param activationFunc func to apply
 */
Dense::Dense(Matrix& w, Matrix& bias, ActivationType func) : _activationFunc(func)
{
    _weights = w;
    _bias = bias;
}

/**
 * getter method for _w field
 * @return weight matrix
 */
Matrix &Dense::getWeights()
{
    return _weights;
}

/**
 * getter method for bias field
 * @return bias matrix
 */
Matrix &Dense::getBias()
{
    return _bias;
}

/**
 * getter method for _activationFunc field
 * @return activation func type
 */
Activation Dense::getActivation()
{
    return (Activation)_activationFunc;
}

/**
 * gets matrix and applies  calculation on it
 * @param mat to calculate and compute
 * @return mat after calculations
 */
Matrix &Dense::operator()(Matrix &mat)
{
    Matrix tempMatrix(_weights.getRows(), mat.getCols());
    tempMatrix = ((_weights * mat) + this->_bias);
    Activation activation(_activationFunc);
    mat = activation(tempMatrix);
    return mat;
}






