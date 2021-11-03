#include "MlpNetwork.h"

/**
 * ctor of MlpNetwork class
 * @param w a pointer to array of 4 weight matrix
 * @param b a pointer to array of 4 bias matrix
 */
MlpNetwork::MlpNetwork(Matrix *w, Matrix *b)
{
    for (int i = 0; i < MLP_SIZE; i++)
    {
        this->_weights[i] = w[i];
        this->_biases[i] = b[i];
    }
}

/**
 * gets marix from binary file wth img of num to proccess
 * @param img a matrix that represents the img in matrix
 * @return the final solution of code that identified the img
 */
Digit MlpNetwork::operator()(Matrix &mat)
{
    Dense leyer1 = Dense(_weights[0], _biases[0], Relu);
    Dense leyer2 = Dense(_weights[1], _biases[1], Relu);
    Dense leyer3 = Dense(_weights[2], _biases[2], Relu);
    Dense leyer4 = Dense(_weights[3], _biases[3], Softmax);

    Matrix step1 = leyer1(mat);
    Matrix step2 = leyer2(step1);
    Matrix step3 = leyer3(step2);
    Matrix solution = leyer4(step3);

    float maxPropabilaty = 0;
    int indexOfMaxProp = 0;
    for (int i = 0; i < solution.getCols() * solution.getRows(); i++)
    {
        if (solution[i] > maxPropabilaty)
        {
            maxPropabilaty = solution[i];
            indexOfMaxProp = i;
        }
    }
    Digit final;
    final.value = indexOfMaxProp;
    final.probability = maxPropabilaty;
    return final;
}
