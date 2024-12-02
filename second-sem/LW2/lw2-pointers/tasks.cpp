#include "tasks.h"

#include <limits>

int mult_neg_elems_above_diag(const int* const arr_start, int height, int width) {
    bool neg_found = false;
    int mult = 1;
    int shift = 0;
    const int *arr_cur = arr_start;
    const int *arr_end = arr_start + height*width;
    while(arr_cur < arr_end) {
        if((arr_cur - arr_start) % width == 0) {
            arr_cur += ++shift;
        }
        if(*arr_cur < 0) {
            neg_found = true;
            mult *= *arr_cur;
        }
        arr_cur++;
    }
    if(!neg_found)
        return 0;
    return mult;
}

int min_uneven_elems(const int* arr, int height, int width) {
    bool uneven_found = false;
    int min = std::numeric_limits<int>::max();
    const int* arr_end = arr + height*width;
    while(arr < arr_end) {
        if(*arr % 2 != 0) {
            uneven_found = true;
            min = *arr < min ? *arr : min;
        }
        arr++;
    }
    if(!uneven_found)
        return 0;
    return min;
}
