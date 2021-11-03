#include <fstream>
#include "Matrix.h"

using std::cout;
using std::endl;
using std::cerr;

//description
/**
 * ctor of Matrix class sets dimension according to rows and cols
 * and sets all values to 0
 * @param rows gets num of rows in matrix
 * @param cols gets num of cols in matrix
 */
Matrix::Matrix(const int rows, const int cols)
{
    if (rows <= 0 || cols <= 0)
    {
        cerr << "Error: rows and cols should be greater then 0." << endl;
        exit(EXIT_FAILURE);
    }
    this->_rows = rows;
    this->_cols = cols;
    this->_matrix = new float [rows * cols];
    if (_matrix == nullptr)
    {
        cerr << "Error: memory allocation failed." << endl;
        exit(EXIT_FAILURE);
    }
    for (int q = 0; q < rows * cols; q++)
    {
        this->_matrix[q] = 0.0;
    }
}

/**
 * default ctor builds a matrix size 1*1 with single value of 0
 */
Matrix::Matrix() : Matrix(1, 1){}

/**
 * copy ctor gets a matrix and builds a new identical matrix
 * @param m matrix to duplicate
 */
Matrix::Matrix(const Matrix &other) : Matrix(other.getRows(), other.getCols())
{
    for (int q = 0; q < this->getRows() * this->getCols(); q++)
    {
        this->_matrix[q] = other._matrix[q];
    }
}

/**
 * matrix destructor frees allocated memory in matrix
 */
Matrix::~Matrix()
{
    delete [] _matrix;
}

//methods

/**
 * getter method gets num of rows
 * @return num of rows in matrix
 */
int Matrix::getRows() const
{
    return  _rows;
}

/**
 * getter method gets num of cols
 * @return gets num of cols in matrix
 */
int Matrix::getCols() const
{
    return _cols;
}

/**
 * gets a matrix and vectorize th e matrix
 * @return vector of given matrix
 */
Matrix &Matrix::vectorize()
{
    if (this->_rows < 1 || this->_cols < 1)
    {
        cerr << "Error: rows and cols should be greater then 0." << endl;
        exit(EXIT_FAILURE);
    }
    _rows *= _cols;
    _cols = 1;
    return *this;
}

/**
 * print all values of matrix
 */
void Matrix::plainPrint() const
{
    for (int i = 0; i < this->getRows(); i++)
    {
        for (int j = 0; j < this->getCols(); j++)
        {
            cout << (*this)(i, j) << " ";
        }
        cout << endl;
    }
}

//operators

/**
 * assignment operator
 * @param rhs matrix to assign from
 * @return *this after assigning operation and passing all values to *this
 */
Matrix &Matrix::operator=(const Matrix &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    if(rhs._rows > 0 && rhs._cols > 0)
    {
        delete [] _matrix;
        this->_rows = rhs._rows;
        this->_cols = rhs._cols;
        this->_matrix = new float [rhs.getRows() * rhs.getCols()];
        for(int i = 0; i < rhs.getRows() * rhs.getCols(); i++)
        {
            (*this)[i] = rhs[i];
        }
        return *this;
    }
    else
    {
        cerr << "Error: rows and cols should be of same size." << endl;
        exit(EXIT_FAILURE);
    }
}

/**
 * matrix multiplication
 * @param rhs matrix to multi with
 * @return new matrix with values of *this an rhs multi
 */
Matrix Matrix::operator*(const Matrix &rhs) const
{
    if (this->getCols() != rhs.getRows())
    {
        cerr  << "Error: cols of this and rows of rhs should be of same size." << endl;
        exit(EXIT_FAILURE);
    }
    Matrix newMatrix(this->getRows(), rhs.getCols());
    for  (int i = 0; i < newMatrix.getRows(); i++)
    {
        for (int j = 0; j < newMatrix.getCols(); j++)
        {
            float x = 0;
            int k = this->getCols();
            for (int q = 0; q < k; q++)
            {
                x += (*this)(i, q) * rhs(q, j);
            }
            newMatrix._matrix[i + j] = x;

        }
    }
    return newMatrix;
}

/**
 * matrix multi with scalar from right
 * @param scalar to multi matrix
 * @return new matrix after multi calculation
 */
 Matrix Matrix::operator*(float scalar)
{
    Matrix newMatrix(this->getRows(), this->getCols());
    for (int i = 0; i < this->getRows() * this->getCols(); i++)
    {
        newMatrix._matrix[i] = this->_matrix[i] * scalar;
    }
    return newMatrix;
}

/**
 * matrix multi with scalar from left
 * @param scalar to multi with
 * @param m matrix to multi scalar with
 * @return new
 */
 Matrix operator*(float scalar, const Matrix &m)
{
    Matrix newMatrix(m.getRows(), m.getCols());
    for (int i = 0; i < m.getRows() * m.getCols(); i++)
    {
        newMatrix._matrix[i] = m._matrix[i] * scalar;
    }
    return newMatrix;
}

/**
  * + operator overloading for matrix
  * @param rhs matrix to add to *this
  * @return a new matrix with connected valied of this and rhs
  */
Matrix Matrix::operator+(const Matrix &rhs) const
{
    if (this->getRows() != rhs.getRows() || this->getCols() != rhs.getCols())
    {
        cerr << "Error: size of both matrix should be equal." << endl;
        exit(EXIT_FAILURE);
    }
    Matrix newMatrix(this->getRows(), this->getCols());
    for (int i = 0; i < this->getRows() * this->getCols(); i++)
    {
        newMatrix._matrix[i] = this->_matrix[i] + rhs._matrix[i];
    }
    return newMatrix;
}

/**
 * += operator allows concatenation
 * @param rhs matrix to combine
 * @return *this after adding rhs matrix
 */
Matrix Matrix::operator+=(const Matrix &rhs)
{
    if (this->getRows() != rhs.getRows() || this->getCols() != rhs.getCols())
    {
        cerr << "Error: size of both matrix should be equal." << endl;
        exit(EXIT_FAILURE);
    }
    for (int i = 0;  i < this->getRows() * this->getCols(); i++)
    {
        this->_matrix[i] += rhs._matrix[i];
    }
    return *this;
}

/**
 * gets the value from matrix with given rows and cols index
 * @param i row index
 * @param j cols index
 * @return value of index in matrix
 */
float &Matrix::operator()(int i, int j)
{
    if (this->getRows() <= i || this->getCols() <= j || i < 0 || j < 0)
    {
        cerr << "Error: index out of bound." << endl;
        exit(EXIT_FAILURE);
    }
    return this->_matrix[i * this->_cols + j];
}

/**
 * gets the value from matrix with given rows and cols index
 * @param i row index
 * @param j cols index
 * @return value of index in matrix
 */
float Matrix::operator()(int i, int j) const
{
    if (this->getRows() <= i || this->getCols() <= j || i < 0 || j < 0)
    {
        cerr << "Error: index out of bound." << endl;
        exit(EXIT_FAILURE);
    }
    return this->_matrix[i * this->getCols() + j];
}

/**
 * gets value in matrix given a single index
 * @param i index to get value from
 * @return value of matrix in given index
 */
float Matrix::operator[](int i) const
{
    if (i >= this->getRows() * this->getCols() || i < 0)
    {
        cerr << "Error: index out of bound." << endl;
        exit(EXIT_FAILURE);
    }
    return this->_matrix[i];
}

/**
 * gets value in matrix given a single index
 * @param i index to get value from
 * @return value of matrix in given index
 */
float &Matrix::operator[](int i)
{
    if (i >= this->getRows() * this->getCols() || i < 0)
    {
        cerr << "Error: index out of bound." << endl;
        exit(EXIT_FAILURE);
    }
    return this->_matrix[i];
}

/**
 * input stream operator overloading for matrix class
 * @param inputStream input stream
 * @param mat matrix to gets all  values we get from stream
 * @return
 */
std::istream &operator>>(std::istream &inputStream, Matrix &mat)
{
    if (!inputStream)
    {
        cerr << "Error: opening and reading file failed." << endl;
        exit(EXIT_FAILURE);
    }
    inputStream.seekg(0, std::ios::beg);
    for (int i = 0; i < mat.getRows() * mat.getCols(); i++)
    {
        inputStream.read((char*) (&mat[i]), 4);
    }
    if (inputStream.peek() != EOF)
    {
        cerr << "Error: didnt read entire file." << endl;
        exit(EXIT_FAILURE);
    }
    return inputStream;
}

/**
 * output stream overloading for matrix class prints img and conclusion
 * @param outputStream output stream
 * @param mat to print from
 * @return printing img and conclusion
 */
std::ostream &operator<<(std::ostream &outputStream, Matrix &mat)
{
    for (int i = 0; i < mat.getRows(); i++)
    {
        for (int j = 0; j < mat.getCols(); j++)
        {
            if (mat(i, j) <= 0.1f)
            {
                outputStream << "  ";
            }
            else
            {
                outputStream << "**";
            }
        }
        outputStream << endl;
    }
    return outputStream;
}


















