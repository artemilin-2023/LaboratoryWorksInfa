//
// Created by y7o4ka on 17.10.2024.
//

#include "searches.h"


search_result timed_better_linear_search(int *array, int size, int needle) {
    auto start = std::chrono::high_resolution_clock::now();

    ...

    auto end = std::chrono::high_resolution_clock::now();

    return {end - start, 0};
}

search_result counted_better_linear_search(int *array, int size, int needle) {
    long comparison_count = 0;

    ...

    return {0, comparison_count};
}

search_result better_linear_search(int *array, int size, int needle) {
    return {timed_better_linear_search(array, size, needle).time_taken,
            counted_better_linear_search(array, size, needle).comparison_count};
};


search_result timed_sentinel_linear_search(int *array, int size, int needle) {
    auto start = std::chrono::high_resolution_clock::now();

    ...

    auto end = std::chrono::high_resolution_clock::now();
    return {end - start, 0};
}

search_result counted_sentinel_linear_search(int *array, int size, int needle) {
    long comparison_count = 0;

    ...

    return {0, comparison_count};
}

search_result sentinel_linear_search(int *array, int size, int needle) {
    return {timed_sentinel_linear_search(array, size, needle).time_taken,
            counted_sentinel_linear_search(array, size, needle).comparison_count};
};


search_result timed_ordered_array_search(int *array, int size, int needle) {
    auto start = std::chrono::high_resolution_clock::now();

    ...

    auto end = std::chrono::high_resolution_clock::now();
    return {end - start, 0};
}

search_result ordered_array_search(int *array, int size, int needle) {
    return {timed_sentinel_linear_search(array, size, needle).time_taken,
            0};
};


search_result timed_binary_search(int *array, int size, int needle) {
    auto start = std::chrono::high_resolution_clock::now();

    ...

    auto end = std::chrono::high_resolution_clock::now();
    return {end - start, 0};
}

search_result binary_search(int *array, int size, int needle) {
    return {timed_sentinel_linear_search(array, size, needle).time_taken,
            counted_sentinel_linear_search(array, size, needle).comparison_count};
};
