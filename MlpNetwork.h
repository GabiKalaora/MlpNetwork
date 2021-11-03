//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Matrix.h"
#include "Dense.h"

#include "Digit.h"

#define MLP_SIZE 4

const MatrixDims imgDims = {28, 28};
const MatrixDims weightsDims[] = {{128, 784}, {64, 128}, {20, 64}, {10, 20}};
const MatrixDims biasDims[]    = {{128, 1}, {64, 1}, {20, 1},  {10, 1}};

/**
 * MlpNetwork class is main function to handle all 4 matrix
 * of wegiths and biases and to distribute them to the right functions off plan
 */
class MlpNetwork
{
private:
    /**
     * an array of 4 weights matrix for calculation of img
     */
    Matrix _weights[MLP_SIZE];
    /**
     * an array of 4 bias matrix for calculation of img
     */
    Matrix _biases[MLP_SIZE];
public:
    /**
     * ctor of MlpNetwork class
     * @param w a pointer to array of 4 weight matrix
     * @param b a pointer to array of 4 bias matrix
     */
    MlpNetwork(Matrix w[MLP_SIZE], Matrix b[MLP_SIZE]);
    /**
     * gets marix from binary file wth img of num to proccess
     * @param img a matrix that represents the img in matrix
     * @return the final solution of code that identified the img
     */
    Digit operator()(Matrix &img);
};


#endif // MLPNETWORK_H
