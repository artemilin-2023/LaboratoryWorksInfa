//
// Created by y7o4ka on 26.10.2024.
//

#include <iostream>
#include "../searches.h"

using hrc = std::chrono::high_resolution_clock;


int timed_binary_search(int const *const array, int size, int needle, search_result &res) {
    auto start = hrc::now();

    int low = 0, high = size - 1;

    while (low <= high) {
        int mid = ((high - low) >> 1) + low;

        if (array[mid] > needle) {
            // what we're searching is to the left of mid
            high = mid - 1;
        } else if (array[mid] < needle) {
            // to the right of mid
            low = mid + 1;
        } else {
            // found
            res.time_taken = hrc::now() - start;
            return mid;
        }
    }
    // not found
    res.time_taken = hrc::now() - start;
    return -1;
}

search_result binary_search(int const *const array, int size, int needle, int correct_index) {
    search_result res{};

    std::cout << "Starting timed BS. Correct index: " << correct_index << ". Got: ";
    int timed_index = timed_binary_search(array, size, needle, res);
    std::cout << timed_index << ". " << (timed_index == correct_index ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!")
              << '\n';

    return res;
};