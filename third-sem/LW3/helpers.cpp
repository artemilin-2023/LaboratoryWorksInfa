//
// Created by y7o4ka on 17.10.2024.
//

#include <random>
#include <algorithm>
#include "helpers.h"


// creates an array of given length filled with random integers from interval
int *generate_array(int length, int min, int max, std::mt19937 &gen) {
    std::uniform_int_distribution<int> dist(min, max);

    int *arr = new int[length];

    // use the rng to fill the array with uniformly distributed integers
    std::generate(arr, arr + length, [&]() { return dist(gen); });

    return arr;
}

bool check_arrays_equal(const int *const arr1, const int *const arr2, int size) {
    for (int i = 0; i < size; ++i)
        if (arr1[i] != arr2[i])
            return false;
    return true;
}
