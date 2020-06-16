#include <iostream>
#include <vector>
#include <random>

#include "lib_v1/matrix.h"

int main() {
    ml::matrix<float> a = {
        {3, 2, 1},
        {1, 0, 2},
    };

    ml::matrix<float> b = {
        {1, 2},
        {0, 1},
        {4, 0}
    };

    std::cout << a % b << std::endl;
    return 0;
}