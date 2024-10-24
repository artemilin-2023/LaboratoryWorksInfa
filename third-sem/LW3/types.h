//
// Created by y7o4ka on 17.10.2024.
//

#ifndef LW_TYPES_H
#define LW_TYPES_H

#include <chrono>
#include <string>

struct needle_def {
    int needle; // duh
    int correct_index; // index where this needle was located
    bool should_restore_needle; // false if the needle should not be put into the array after making only one of them
    std::string name;
};

struct sort_result {
    std::chrono::high_resolution_clock::duration time_taken;
    long comparison_count;
    long swap_count;
};

typedef sort_result (*int_sort_func)(int const *const array, int size, int const *const sorted_array);

struct sort_with_name {
    int_sort_func func;
    std::string name;
};

#endif //LW_TYPES_H
