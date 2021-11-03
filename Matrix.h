// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

/**
 * @struct MatrixDims
 * @brief Matrix dimensions container
 */
typedef struct MatrixDims
{
    int rows, cols;
} MatrixDims;

/**
 * Matrix class holds all fields for representing a matrix and appropriate methods
 * for maintaining matrix with calculation and indexing features
 */
class Matrix
{
private:
    /**
     * fields of matrix both dimension of matrix and an one dimension array
     * that holds matrix value
     */
    int _rows, _cols;
    float *_matrix{};
public:
    //Description
    /**
     * ctor of Matrix class sets dimension according to rows and cols
     * and sets all values to 0
     * @param rows gets num of rows in matrix
     * @param cols gets num of cols in matrix
     */
    Matrix(int rows, int cols);
    /**
     * default ctor builds a matrix size 1*1 with single value of 0
     */
    Matrix();
    /**
     * copy ctor gets a matrix and builds a new identical matrix
     * @param m matrix to duplicate
     */
    Matrix(const Matrix &m);
    /**
     * matrix destructor frees allocated memory in matrix
     */
    ~Matrix();

    //Methods
    /**
     * getter method gets num of rows
     * @return num of rows in matrix
     */
    [[nodiscard]] int getRows() const;
    /**
     * getter method gets num of cols
     * @return gets num of cols in matrix
     */
    [[nodiscard]] int getCols() const;
    /**
     * gets a matrix and vectorize th e matrix
     * @return vector of given matrix
     */
    Matrix &vectorize();
    /**
     * print all values of matrix
     */
    void plainPrint() const;

    //Operators

    /**
     * assignment operator
     * @param rhs matrix to assign from
     * @return *this after assigning operation and passing all values to *this
     */
    Matrix &operator=(const Matrix &rhs);
    /**
     * matrix multiplication
     * @param rhs matrix to multi with
     * @return new matrix with values of *this an rhs multi
     */
    Matrix operator*(const Matrix &rhs) const ;
    /**
     * matrix multi with scalar from right
     * @param scalar to multi matrix
     * @return new matrix after multi calculation
     */
    Matrix operator*(float scalar);
    /**
     * matrix multi with scalar from left
     * @param scalar to multi with
     * @param m matrix to multi scalar with
     * @return new
     */
    friend Matrix operator*(float scalar, const Matrix &m);
    /**
     * + operator overloading for matrix
     * @param rhs matrix to add to *this
     * @return a new matrix with connected valied of this and rhs
     */
    Matrix operator+(const Matrix &rhs) const;
    /**
     * += operator allows concatenation
     * @param rhs matrix to combine
     * @return *this after adding rhs matrix
     */
    Matrix operator+=(const Matrix &rhs);
    /**
     * gets the value from matrix with given rows and cols index
     * @param i row index
     * @param j cols index
     * @return value of index in matrix
     */
    float operator()(int i, int j) const;
    /**
     * gets the value from matrix with given rows and cols index
     * @param i row index
     * @param j cols index
     * @return value of index in matrix
     */
    float &operator()(int i, int j);
    /**
     * gets value in matrix given a single index
     * @param i index to get value from
     * @return value of matrix in given index
     */
    float operator[](int i) const;
    /**
     * gets value in matrix given a single index
     * @param i index to get value from
     * @return value of matrix in given index
     */
    float &operator[](int i);
    /**
     * input stream operator overloading for matrix class
     * @param inputStream input stream
     * @param mat matrix to gets all  values we get from stream
     * @return
     */
    friend std::istream &operator >>(std:: istream &inputStream, Matrix &mat);
    /**
     * output stream overloading for matrix class prints img and conclusion
     * @param outputStream output stream
     * @param mat to print from
     * @return printing img and conclusion
     */
    friend std::ostream &operator <<(std:: ostream &outputStream, Matrix &mat);
};

#endif //MATRIX_H
