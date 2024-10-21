//
// Created by y7o4ka on 17.10.2024.
//

#ifndef LW_TYPES_H
#define LW_TYPES_H

#include <chrono>
#include <string>


struct search_result {
    std::chrono::high_resolution_clock::duration time_taken;
    long comparison_count;
};

typedef search_result (*int_search_func)(int *array, int size, int needle);

struct search_with_name {
    int_search_func func;
    std::string name;
};

#endif //LW_TYPES_H
