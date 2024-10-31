//
// Created by y7o4ka on 24.10.2024.
//

#ifndef LW_SORTS_H
#define LW_SORTS_H


#include "types.h"

sort_result quick_sort_hoare(int const *array, int size, int const *sorted_array);
void quick_sort_hoare_with_steps(int *array, int size);

sort_result quick_sort_last(int const *array, int size, int const *sorted_array);
void quick_sort_last_with_steps(int *array, int size);

sort_result quick_sort_median_of_3(int const *array, int size, int const *sorted_array);
void quick_sort_median_of_3_with_steps(int *array, int size);

sort_result selection_sort(int const *array, int size, int const *sorted_array);
void selection_sort_with_steps(int *array, int size);


#endif //LW_SORTS_H
