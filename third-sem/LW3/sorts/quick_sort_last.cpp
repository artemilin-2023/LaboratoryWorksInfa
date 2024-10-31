//
// Created by y7o4ka on 26.10.2024.
//

#include <chrono>
#include <iostream>
#include <memory>
#include <stack>

#include "../sorts.h"
#include "../helpers.h"

using hrc = std::chrono::high_resolution_clock;


void timed_quick_sort_last(int *const array, int size, sort_result &res) {
    auto start = hrc::now();

    std::stack<std::pair<int, int>> sort_stack{};

    sort_stack.emplace(0, size - 1);

    while (!sort_stack.empty()) {
        auto [low_i, high_i] = sort_stack.top();
        sort_stack.pop();
        if (low_i >= high_i)
            continue;

        int pivot = array[high_i];
        int i = low_i;

        for (int j = low_i; j < high_i; ++j) {
            if (array[j] <= pivot) {
                std::swap(array[i], array[j]);
                ++i;
            }
        }
        std::swap(array[i], array[high_i]);

        sort_stack.emplace(low_i, i - 1);
        sort_stack.emplace(i + 1, high_i);
    }

    res.time_taken = hrc::now() - start;
}

void counted_quick_sort_last(int *const array, int size, sort_result &res) {
    std::stack<std::pair<int, int>> sort_stack{};

    sort_stack.emplace(0, size - 1);

    while (!sort_stack.empty()) {
        auto [low_i, high_i] = sort_stack.top();
        sort_stack.pop();

        ++res.comparison_count;
        if (low_i >= high_i)
            continue;

        int pivot = array[high_i];
        int i = low_i;

        for (int j = low_i; ++res.comparison_count, j < high_i; ++j) {
            ++res.comparison_count;
            if (array[j] <= pivot) {
                ++res.swap_count;
                std::swap(array[i], array[j]);
                ++i;
            }
        }
        ++res.swap_count;
        std::swap(array[i], array[high_i]);

        sort_stack.emplace(low_i, i - 1);
        sort_stack.emplace(i + 1, high_i);
    }
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

void quick_sort_last_with_steps(int *array, int size) {
    std::cout << "Исходный массив:\n";
    print_array(array, size);

    std::stack<std::pair<int, int>> sort_stack{};
    sort_stack.emplace(0, size - 1);

    while (!sort_stack.empty()) {
        auto [low_i, high_i] = sort_stack.top();
        sort_stack.pop();
        if (low_i >= high_i)
            continue;

        std::cout << "Сортируем подмассив:\n";
        print_array(array, size, {low_i, high_i});
        std::cout << "Опорным элементом берём последний элемент подмассива\n";

        int pivot = array[high_i];
        int i = low_i;

        for (int j = low_i; j < high_i; ++j) {
            std::cout << j << "-й элемент ";
            if (array[j] <= pivot) {
                std::cout << "меньше опорного. Переставим его с первым элементом больше опорного\n";
                std::swap(array[i], array[j]);
                print_array(array, size, {i, j});
                ++i;
            } else {
                std::cout << "больше опорного. Оставим его не месте.\n";
            }
        }
        std::cout << "Поставим опорный элемент между большими и меньшими, переставив его с первым большим\n";
        std::swap(array[i], array[high_i]);
        print_array(array, size, {i, high_i});

        sort_stack.emplace(low_i, i - 1);
        sort_stack.emplace(i + 1, high_i);
    }
}
