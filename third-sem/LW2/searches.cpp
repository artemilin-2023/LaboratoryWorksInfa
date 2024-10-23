//
// Created by y7o4ka on 17.10.2024.
//

#include "searches.h"


using hrc = std::chrono::high_resolution_clock;


auto timed_better_linear_search(int const *const array, int size, int needle) {
    auto start = hrc::now();

    for (int i = 0; i < size; ++i) {
        if (array[i] == needle)
            return hrc::now() - start;
    }

    return hrc::now() - start;
}

long counted_better_linear_search(int const *const array, int size, int needle) {
    long comparison_count = 0;

    for (int i = 0; i < size; ++i) {
        comparison_count++;
        if (array[i] == needle)
            return comparison_count;
    }

    return comparison_count;
}

search_result better_linear_search(int const *const array, int size, int needle) {
    return {timed_better_linear_search(array, size, needle),
            counted_better_linear_search(array, size, needle)};
};


auto timed_sentinel_linear_search(int const *const array, int size, int needle) {
    auto start = hrc::now();

//    ...

    auto end = hrc::now();
    return end - start;
}

long counted_sentinel_linear_search(int const *const array, int size, int needle) {
    long comparison_count = 0;

//    ...

    return comparison_count;
}

search_result sentinel_linear_search(int const *const array, int size, int needle) {
    return {timed_sentinel_linear_search(array, size, needle),
            counted_sentinel_linear_search(array, size, needle)};
};


auto timed_ordered_array_search(int const *const array, int size, int needle) {
    auto start = hrc::now();

//    ...

    auto end = hrc::now();
    return end - start;
}

search_result ordered_array_search(int const *const array, int size, int needle) {
    return {timed_ordered_array_search(array, size, needle), 0};
};


auto timed_binary_search(int const *const array, int size, int needle) {
    auto start = hrc::now();

//    ...

    auto end = hrc::now();
    return end - start;
}

search_result binary_search(int const *const array, int size, int needle) {
    return {timed_binary_search(array, size, needle), 0};
};
