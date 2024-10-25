//
// Created by y7o4ka on 24.10.2024.
//

#include <chrono>
#include <functional>
#include <iostream>
#include <memory>

#include "sorts.h"
#include "types.h"
#include "helpers.h"

using hrc = std::chrono::high_resolution_clock;


void timed_selection_sort(int *const array, int size, sort_result &res) {
    auto start = hrc::now();
    
    for (int i = 0; i < size; ++i) {
        int min_i = i;
        for (int j = i + 1; j < size; ++j) {
            if (array[j] < array[min_i])
                min_i = j;
        }
        std::swap(array[i], array[min_i]);
    }

    res.time_taken = hrc::now() - start;
}

void counted_selection_sort(int *const array, int size, sort_result &res) {
    for (int i = 0; ++res.comparison_count, i < size; ++i) {
        int min_i = i;
        for (int j = i + 1; ++res.comparison_count, j < size; ++j) {
            ++res.comparison_count;
            if (array[j] < array[min_i])
                min_i = j;
        }
        ++res.swap_count;
        std::swap(array[i], array[min_i]);
    }
}

sort_result selection_sort(int const *const array, int size, int const *const sorted_array) {
    auto temp_array = std::make_unique_for_overwrite<int[]>(size);

    sort_result res{};

    std::cout << "Starting timed SELECTION SORT. Got: " << std::flush;
    std::copy(array, array + size, temp_array.get());
    timed_selection_sort(temp_array.get(), size, res);
    std::cout << (check_arrays_equal(temp_array.get(), sorted_array, size) ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    std::cout << "Starting counted SELECTION SORT. Got: " << std::flush;
    std::copy(array, array + size, temp_array.get());
    counted_selection_sort(temp_array.get(), size, res);
    std::cout << (check_arrays_equal(temp_array.get(), sorted_array, size) ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    return res;
};

void timed_quick_sort_last(int *const array, int size, sort_result &res) {
    auto start = hrc::now();

    auto quick_sort = [](this const auto &self, int *const arr, int low, int high) {
        if (low >= high)
            return;

        int pivot = arr[high];
        int i = low-1;

        for (int j = low; j < high; ++j) {
            if (arr[j] <= pivot) {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i+1], arr[high]);
        
        int pivot_i = i+1;

        self(arr, low, pivot_i-1);
        self(arr, pivot_i+1, high);
    };

    quick_sort(array, 0, size-1);

    res.time_taken = hrc::now() - start;
}

void counted_quick_sort_last(int *const array, int size, sort_result &res) {
    ++res.comparison_count;
}

sort_result quick_sort_last(int const *const array, int size, int const *const sorted_array) {
    auto temp_array = std::make_unique_for_overwrite<int[]>(size);

    sort_result res{};

    std::cout << "Starting timed QUICK SORT LAST. Got: " << std::flush;
    std::copy(array, array + size, temp_array.get());
    timed_quick_sort_last(temp_array.get(), size, res);
    std::cout << (check_arrays_equal(temp_array.get(), sorted_array, size) ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    std::cout << "Starting counted QUICK SORT LAST. Got: " << std::flush;
    std::copy(array, array + size, temp_array.get());
    counted_quick_sort_last(temp_array.get(), size, res);
    std::cout << (check_arrays_equal(temp_array.get(), sorted_array, size) ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    return res;
};


void timed_quick_sort_median(int *const array, int size, sort_result &res) {
    auto start = hrc::now();


    res.time_taken = hrc::now() - start;
}

void counted_quick_sort_median(int *const array, int size, sort_result &res) {
    ++res.comparison_count;
}

sort_result quick_sort_median(int const *const array, int size, int const *const sorted_array) {
    auto temp_array = std::make_unique_for_overwrite<int[]>(size);

    sort_result res{};

    std::cout << "Starting timed QUICK SORT MEDIAN. Got: " << std::flush;
    std::copy(array, array + size, temp_array.get());
    timed_quick_sort_median(temp_array.get(), size, res);
    std::cout << (check_arrays_equal(temp_array.get(), sorted_array, size) ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    std::cout << "Starting counted QUICK SORT MEDIAN. Got: " << std::flush;
    std::copy(array, array + size, temp_array.get());
    counted_quick_sort_median(temp_array.get(), size, res);
    std::cout << (check_arrays_equal(temp_array.get(), sorted_array, size) ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    return res;
};


void timed_quick_sort_hoare(int *const array, int size, sort_result &res) {
    auto start = hrc::now();


    res.time_taken = hrc::now() - start;
}

void counted_quick_sort_hoare(int *const array, int size, sort_result &res) {
    ++res.comparison_count;
}

sort_result quick_sort_hoare(int const *const array, int size, int const *const sorted_array) {
    auto temp_array = std::make_unique_for_overwrite<int[]>(size);

    sort_result res{};

    std::cout << "Starting timed QUICK SORT HOARE. Got: " << std::flush;
    std::copy(array, array + size, temp_array.get());
    timed_quick_sort_hoare(temp_array.get(), size, res);
    std::cout << (check_arrays_equal(temp_array.get(), sorted_array, size) ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    std::cout << "Starting counted QUICK SORT HOARE. Got: " << std::flush;
    std::copy(array, array + size, temp_array.get());
    counted_quick_sort_hoare(temp_array.get(), size, res);
    std::cout << (check_arrays_equal(temp_array.get(), sorted_array, size) ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    return res;
};

