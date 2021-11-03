//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H
#include "Matrix.h"
#include <cmath>

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    Relu,
    Softmax
};

/**
 * builds nad activation (Relu and Softmax) functions
 */
class Activation
{
private:
    /**
     * gets activation type fund nedded
     */
    ActivationType _activationFunc;
    /**
     * Relu func
     * @param mat to applay Relu fun on
     * @return a new func after applied Relu func on matrix
     */
    static Matrix _reluFunc(Matrix &mat);
    /**
     * Softmax func
     * @param mat to applay Softmax fun on
     * @return a new func after applied Softmax func on matrix
     */
    static Matrix _softmaxFunc(Matrix &mat);

public:
    /**
     * ctor for Activation class
     * @param activationType
     */
    explicit Activation(ActivationType activationType);
    /**
     * getter method for _activationType field
     * @return type of func wanted
     */
    [[nodiscard]] ActivationType getActivationType() const;
    /**
     * applies appropriate func on given matrix
     * @param mat to apply fuc on
     * @return a new matrix after applying chosen func
     */
    Matrix operator()(Matrix &mat);
};

#endif //ACTIVATION_H
