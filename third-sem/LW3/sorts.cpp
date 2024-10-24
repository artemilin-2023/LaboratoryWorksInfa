//
// Created by y7o4ka on 24.10.2024.
//

#include <chrono>
#include <iostream>
#include <memory>

#include "sorts.h"
#include "types.h"
#include "helpers.h"

using hrc = std::chrono::high_resolution_clock;


void timed_selection_sort(int const *const array, int size, sort_result &res) {
    auto start = hrc::now();


    res.time_taken = hrc::now() - start;
}

void counted_selection_sort(int const *const array, int size, sort_result &res) {
    ++res.comparison_count;
}

sort_result selection_sort(int const *const array, int size, int const *const sorted_array) {
    auto temp_array = std::make_unique_for_overwrite<int[]>(size);

    sort_result res{};

    std::cout << "Starting timed SELECTION SORT. Got: ";
    std::copy(array, array + size, temp_array.get());
    timed_selection_sort(array, size, res);
    std::cout << (check_arrays_equal(temp_array.get(), sorted_array, size) ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    std::cout << "Starting counted SELECTION SORT. Got: ";
    std::copy(array, array + size, temp_array.get());
    counted_selection_sort(array, size, res);
    std::cout << (check_arrays_equal(temp_array.get(), sorted_array, size) ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    return res;
};


void timed_quick_sort_last(int const *const array, int size, sort_result &res) {
    auto start = hrc::now();


    res.time_taken = hrc::now() - start;
}

void counted_quick_sort_last(int const *const array, int size, sort_result &res) {
    ++res.comparison_count;
}

sort_result quick_sort_last(int const *const array, int size, int const *const sorted_array) {
    auto temp_array = std::make_unique_for_overwrite<int[]>(size);

    sort_result res{};

    std::cout << "Starting timed QUICK SORT LAST. Got: ";
    std::copy(array, array + size, temp_array.get());
    timed_quick_sort_last(array, size, res);
    std::cout << (check_arrays_equal(temp_array.get(), sorted_array, size) ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    std::cout << "Starting counted QUICK SORT LAST. Got: ";
    std::copy(array, array + size, temp_array.get());
    counted_quick_sort_last(array, size, res);
    std::cout << (check_arrays_equal(temp_array.get(), sorted_array, size) ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    return res;
};


void timed_quick_sort_median(int const *const array, int size, sort_result &res) {
    auto start = hrc::now();


    res.time_taken = hrc::now() - start;
}

void counted_quick_sort_median(int const *const array, int size, sort_result &res) {
    ++res.comparison_count;
}

sort_result quick_sort_median(int const *const array, int size, int const *const sorted_array) {
    auto temp_array = std::make_unique_for_overwrite<int[]>(size);

    sort_result res{};

    std::cout << "Starting timed QUICK SORT MEDIAN. Got: ";
    std::copy(array, array + size, temp_array.get());
    timed_quick_sort_median(array, size, res);
    std::cout << (check_arrays_equal(temp_array.get(), sorted_array, size) ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    std::cout << "Starting counted QUICK SORT MEDIAN. Got: ";
    std::copy(array, array + size, temp_array.get());
    counted_quick_sort_median(array, size, res);
    std::cout << (check_arrays_equal(temp_array.get(), sorted_array, size) ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    return res;
};


void timed_quick_sort_hoare(int const *const array, int size, sort_result &res) {
    auto start = hrc::now();


    res.time_taken = hrc::now() - start;
}

void counted_quick_sort_hoare(int const *const array, int size, sort_result &res) {
    ++res.comparison_count;
}

sort_result quick_sort_hoare(int const *const array, int size, int const *const sorted_array) {
    auto temp_array = std::make_unique_for_overwrite<int[]>(size);

    sort_result res{};

    std::cout << "Starting timed QUICK SORT HOARE. Got: ";
    std::copy(array, array + size, temp_array.get());
    timed_quick_sort_hoare(array, size, res);
    std::cout << (check_arrays_equal(temp_array.get(), sorted_array, size) ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    std::cout << "Starting counted QUICK SORT HOARE. Got: ";
    std::copy(array, array + size, temp_array.get());
    counted_quick_sort_hoare(array, size, res);
    std::cout << (check_arrays_equal(temp_array.get(), sorted_array, size) ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    return res;
};