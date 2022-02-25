#include "linearAlgebra.h"

namespace mt_la {

    matrix::matrix(uint rowCount, uint columnCount) 
    {
        this->rowCount = rowCount;
        this->columnCount = columnCount;
        initialise();
    }
    matrix::matrix(int *array, uint rowCount, uint columnCount) 
        :rowCount(rowCount), columnCount(columnCount)
    {
        initialise();
        for(uint i = 0; i < rowCount * columnCount; i++) {
            uint column = i / rowCount;
            uint row = i % rowCount;
            data[row][column] = array[i];
        }
    }
    matrix::~matrix() {
        for (uint i = 0; i < rowCount; i++) {
            delete[] data[i];
        }
        delete[] data;
    }
    string matrix::getData() {
        std::stringstream matrixData;
        for (uint i = 0; i < this->rowCount; i++) {
            for (uint j = 0; j < this->columnCount; j++) {
                matrixData << this->data[i][j] << "  ";
            }
            matrixData << endl;
        }
        return matrixData.str();
    }
    void matrix::clear() {
        for (uint i = 0; i < rowCount; i++) {
            for (uint j = 0; j < columnCount; j++) {
                data[i][j] = 0;
            }
        }
        pointer = 0;
    }
    void matrix::push(int value) {
        if (pointer < rowCount * columnCount) {
            uint column = pointer / rowCount;
            uint row = pointer % rowCount;
            data[row][column] = value;
            pointer++;
        }
    }
    void matrix::pop() {
        if (pointer > 0) {
            --pointer;
            uint column = pointer / rowCount;
            uint row = pointer % rowCount;
            data[row][column] = 0;
        }
    }
    void matrix::sumData(matrix& matrix) {
        for (uint i = 0; i < rowCount; i++) {
            for (uint j = 0; j < columnCount; j++) {
                data[i][j] += matrix.data[i][j];
            }
        }
    }
    void matrix::multiplyByScalar(int& scalar) {
        for (uint i = 0; i < rowCount; i++) {
            for (uint j = 0; j < columnCount; j++) {
                data[i][j] *= scalar;
            }
        }
    }
    void matrix::operator+=(matrix& matrix) {
        sumData(matrix);
    }
    matrix& matrix::operator+(matrix& matrix) {
        sumData(matrix);
        return *this;
    }
    matrix matrix::operator*(matrix& multiplier) {
        matrix newMatrix = multiplyByMatrix(*this, multiplier);
        return newMatrix;
    }
    void matrix::initialise() {
        data = new int*[rowCount];
        for (uint i = 0; i < rowCount; i++) {
            data[i] = new int[columnCount];
        }
    } 
    void matrix::initialise(uint rowCount, uint columnCount) {
        data = new int*[rowCount];
        for (uint i = 0; i < rowCount; i++) {
            data[i] = new int[columnCount];
        }
    } 

    matrix multiplyByMatrix(matrix& first, matrix& second) {
        matrix newMatrix = matrix(first.rowCount, second.columnCount);
        if (first.columnCount == second.rowCount) {
            for (int i = 0; i < first.rowCount; i++) {
                for (int j = 0; j < second.columnCount; j++) {
                    for (int k = 0; k < first.columnCount; k++) {
                        newMatrix.data[i][j] += first.data[i][k] * second.data[k][j];
                    }
                }
            }
        }
        return newMatrix;
    }
    matrix deleteRow(matrix& oldMatrix, uint row) {
        matrix newMatrix = matrix(oldMatrix.rowCount - 1, oldMatrix.columnCount);
        bool reached = false;
        uint decreasedColum = 0;
        for (uint i = 0; i < oldMatrix.rowCount; i++) {
            for (uint j = 0; j < oldMatrix.columnCount; j++) {
                cout << i << "\t" << j << endl;
                if (i == row) { reached = true; continue; }
                if (reached) {
                    decreasedColum = i - 1;
                    newMatrix.data[decreasedColum][j] = oldMatrix.data[i][j];
                }
                else {
                    newMatrix.data[i][j] = oldMatrix.data[i][j];
                }
            }
        }
        return newMatrix;
    }
    std::ostream& operator<<(std::ostream& stream, matrix& matrix) {
        stream << matrix.getData();
        return stream;
    }

}