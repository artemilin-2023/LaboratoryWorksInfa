//
// Created by y7o4ka on 17.10.2024.
//

#ifndef LW_SEARCHES_H
#define LW_SEARCHES_H


#include "types.h"


search_result better_linear_search(int *array, int size, int needle);

search_result sentinel_linear_search(int *array, int size, int needle);

search_result ordered_array_search(int *array, int size, int needle);

search_result binary_search(int *array, int size, int needle);

#endif //LW_SEARCHES_H
