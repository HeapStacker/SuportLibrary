#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#define EXCEPTION_VAL -666


using std::cout;
using std::endl;
using std::string;
using uint = unsigned int;

namespace mt_la {
    class matrix {
        uint rowCount = 0;
        uint columnCount = 0;
        uint pointer = 0;
        int **data = nullptr;  

        void initialise();
        void initialise(uint rowCount, uint columnCount);
    public:


        matrix(uint rowCount, uint columnCount);
        matrix(int *array, uint rowCount, uint columnCount);
        ~matrix();


        void operator+=(matrix& matrix);
        matrix& operator+(matrix& matrix);
        matrix operator*(matrix& multiplier);


        void clear();
        void push(int value);
        void pop();
        void sumData(matrix& matrix);
        void multiplyByScalar(int& scalar);
        string getData();


        friend matrix multiplyByMatrix(matrix& first, matrix& second);
        friend matrix deleteRow(matrix& oldMatrix, uint row);
        
    };

    std::ostream& operator<<(std::ostream& stream, matrix& matrix);
    
    matrix multiplyByMatrix(matrix& first, matrix& second);
    matrix deleteRow(matrix& oldMatrix, uint row);

}
