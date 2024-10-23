//
// Created by y7o4ka on 17.10.2024.
//

#ifndef LW_TYPES_H
#define LW_TYPES_H

#include <chrono>
#include <string>

struct needle_def {
    int needle; // duh
    int needle_index; // index where this needle was located
    bool should_restore_needle; // false if the needle should not be put into the array after making only one of them
    std::string name;
};

struct search_result {
    std::chrono::high_resolution_clock::duration time_taken;
    long comparison_count;
};

typedef search_result (*int_search_func)(int const *const array, int size, int needle);

struct search_with_name {
    int_search_func func;
    std::string name;
};

#endif //LW_TYPES_H
