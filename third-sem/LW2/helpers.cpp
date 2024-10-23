//
// Created by y7o4ka on 17.10.2024.
//

#include <random>
#include <algorithm>
#include "helpers.h"


// creates an array of given length filled with random integers from interval
int *generate_array(int length, int min, int max, std::mt19937 gen) {
    std::uniform_int_distribution<int> dist(min, max);

    int *arr = new int[length];

    // use the rng to fill the array with uniformly distributed integers
    std::generate(arr, arr + length, [&]() { return dist(gen); });

    return arr;
}

// returns a copied array with this number replaced with a previous one
int *remove_number_from_array(int const *const array, int length, int number_to_remove) {
    int *fixed_array = new int[length];
    std::copy(array, array + length, fixed_array);

    if (fixed_array[0] == number_to_remove)
        fixed_array[0] = 0;
    for (int i = 1; i < length; ++i) {
        if (fixed_array[i] == number_to_remove) {
            fixed_array[i] = fixed_array[i - 1];
        }
    }

    return fixed_array;
}