#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>  //for std::pair maby it'll be needed
#include <stack>  //for std::stack, maby we will need it

using std::vector;
using std::remove;
using std::pair;
using std::stack;

namespace mt_vector {

    template<typename T>
    inline void deleteVector(vector<T>* vector) {
        vector->clear();
        vector->shrink_to_fit();
    }

    template<typename T>
    inline void deleteSpecificElement(vector<T>* vector, T element) {
        vector->erase(remove(vector->begin(), vector->end(), element), vector->end());
    }

}