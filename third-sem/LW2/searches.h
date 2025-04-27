//
// Created by y7o4ka on 17.10.2024.
//

#ifndef LW_SEARCHES_H
#define LW_SEARCHES_H


#include "types.h"

search_result better_linear_search(int const *array, int size, int needle, int correct_index);

search_result sentinel_linear_search(int const *array, int size, int needle, int correct_index);

search_result ordered_array_search(int const *array, int size, int needle, int correct_index);

search_result binary_search(int const *array, int size, int needle, int correct_index);

#endif //LW_SEARCHES_H
