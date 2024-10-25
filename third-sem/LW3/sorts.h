//
// Created by y7o4ka on 24.10.2024.
//

#ifndef LW_SORTS_H
#define LW_SORTS_H


#include "types.h"

sort_result selection_sort(int const *array, int size, int const *sorted_array);

sort_result quick_sort_last(int const *array, int size, int const *sorted_array);

sort_result quick_sort_median_of_3(int const *array, int size, int const *sorted_array);

sort_result quick_sort_hoare(int const *array, int size, int const *sorted_array);


#endif //LW_SORTS_H
