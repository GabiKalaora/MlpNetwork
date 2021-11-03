#ifndef EX4_DENSE_H
#define EX4_DENSE_H

#include "Activation.h"
#include "Matrix.h"

/**
 * gets a weight matrix and a bias matrix and
 * the appropriate func to applay on matrix
 */
class Dense
{
private:
    /**
     * gets a weight matrix
     */
    Matrix _weights;
    /**
     * gets a bias matrix
     */
    Matrix _bias;
    /**
     * right func to apply on given matrix in right stage
     */
    ActivationType _activationFunc;
public:
    //Description
    /**
     * Dense ctor
     * @param w gets a weight matrix
     * @param bias gets a cias matrix
     * @param activationFunc func to apply
     */
    Dense(Matrix &w, Matrix &bias, ActivationType activationFunc);
    //Methods
    /**
     * getter method for _w field
     * @return weight matrix
     */
    Matrix &getWeights();
    /**
     * getter method for bias field
     * @return bias matrix
     */
    Matrix &getBias();
    /**
     * getter method for _activationFunc field
     * @return activation func type
     */
    Activation getActivation();
    //Operators
    /**
     * gets matrix and applies  calculation on it
     * @param mat to calculate and compute
     * @return mat after calculations
     */
    Matrix &operator()(Matrix &mat);
};

#endif //EX4_DENSE_H
