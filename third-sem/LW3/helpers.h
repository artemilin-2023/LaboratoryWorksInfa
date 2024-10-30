//
// Created by y7o4ka on 17.10.2024.
//

#ifndef LW_HELPERS_H
#define LW_HELPERS_H

#include <random>

int *generate_array(int length, int min, int max, std::mt19937 &gen);

bool check_arrays_equal(int const *arr1, int const *arr2, int size);

void print_array(int const *arr, int size, const std::initializer_list<int>& underlined_indices = {});

#endif //LW_HELPERS_H
