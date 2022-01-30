#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;
using std::remove;

namespace mt_vector {

    template<typename T>
    void deleteVector(vector<T>* vector) {
        vector->clear();
        vector->shrink_to_fit();
    }

    template<typename T>
    void deleteSpecificElement(vector<T>* vector, T element) {
        vector->erase(remove(vector->begin(), vector->end(), element), vector->end());
    }

}