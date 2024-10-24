//
// Created by y7o4ka on 17.10.2024.
//

#include <random>
#include <algorithm>
#include <unordered_map>
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
    std::unordered_map<int, int> mp;
    for (int i = 0; i < size; i++)
        mp[arr1[i]]++; // count elems in arr1

    for (int i = 0; i < size; i++) {
        if (mp.find(arr2[i]) == mp.end())
            // element in arr 2 that's not in arr1
            return false;

        if (mp[arr2[i]] == 0)
            // more elems in arr2 than in arr1
            return false;

        mp[arr2[i]]--;
    }
    return true;
}
