//
// Created by y7o4ka on 17.10.2024.
//

#include <memory>
#include <iostream>
#include "searches.h"


using hrc = std::chrono::high_resolution_clock;


int timed_better_linear_search(int const *const array, int size, int needle, search_result &res) {
    auto start = hrc::now();

    for (int i = 0; i < size; ++i) {
        if (array[i] == needle) {
            // found
            res.time_taken = hrc::now() - start;
            return i;
        }
    }
    // not found
    res.time_taken = hrc::now() - start;
    return -1;
}

int counted_better_linear_search(int const *const array, int size, int needle, search_result &res) {
    for (int i = 0; i < size; ++i) {
        ++res.comparison_count; // i < size
        ++res.comparison_count; // a_i == needle
        if (array[i] == needle) {
            // found
            return i;
        }
    }
    // not found
    return -1;
}

search_result better_linear_search(int const *const array, int size, int needle, int correct_index) {
    search_result res{};

    std::cout << "Starting timed BLS. Correct index: " << correct_index << ". Got: ";
    int timed_index = timed_better_linear_search(array, size, needle, res);
    std::cout << timed_index << ". " << (timed_index == correct_index ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!") << '\n';

    std::cout << "Starting counted BLS. Correct index: " << correct_index << ". Got: ";
    int counted_index = counted_better_linear_search(array, size, needle, res);
    std::cout << counted_index << ". " << (counted_index == correct_index ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!") << '\n';

    return res;
};


int timed_sentinel_linear_search(int const *const array, int size, int needle, search_result &res) {
    // the code above works because we don't modify the array (it's the same each time), so we do this just in case
    // it doesn't affect the computation in any way
    std::unique_ptr<int[]> temp_array(new int[size]); // freed when out of scope
    std::copy(array, array + size, temp_array.get());

    auto start = hrc::now();

    int last = temp_array[size-1];
    temp_array[size-1] = needle;

    int i = 0;
    while(temp_array[i] != needle)
        i++;

    temp_array[size-1] = last;

    if((i < size-1) || (temp_array[size-1] == needle)) {
        // found
        res.time_taken = hrc::now() - start;
        return i;
    }
    //not found
    res.time_taken = hrc::now() - start;
    return -1;
}

int counted_sentinel_linear_search(int const *const array, int size, int needle, search_result &res) {
    std::unique_ptr<int[]> temp_array(new int[size]);
    std::copy(array, array + size, temp_array.get());

    int last = temp_array[size-1];
    temp_array[size-1] = needle;

    int i = 0;
    while(temp_array[i] != needle) {
        ++res.comparison_count;
        ++i;
    }

    temp_array[size-1] = last;

    ++res.comparison_count; // check if found
    if(i < size-1)
        // found
        return i;
    ++res.comparison_count; // check the last element too
    if(temp_array[size-1] == needle)
        // found
        return i;
    //not found
    return -1;
}

search_result sentinel_linear_search(int const *const array, int size, int needle, int correct_index) {
    search_result res{};

    std::cout << "Starting timed SLS. Correct index: " << correct_index << ". Got: ";
    int timed_index = timed_sentinel_linear_search(array, size, needle, res);
    std::cout << timed_index << ". " << (timed_index == correct_index ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!") << '\n';

    std::cout << "Starting counted SLS. Correct index: " << correct_index << ". Got: ";
    int counted_index = counted_sentinel_linear_search(array, size, needle, res);
    std::cout << counted_index << ". " << (counted_index == correct_index ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!") << '\n';

    return res;
};


int timed_ordered_array_search(int const *const array, int size, int needle, search_result &res) {
    // idc the reason behind this being its own "algorithm" but honestly idc
    auto start = hrc::now();

    for (int i = 0; i < size; ++i) {
        if (array[i] == needle) {
            // found
            res.time_taken = hrc::now() - start;
            return i;
        }
    }
    // not found
    res.time_taken = hrc::now() - start;
    return -1;
}

search_result ordered_array_search(int const *const array, int size, int needle, int correct_index) {
    search_result res{};

    std::cout << "Starting timed OAS. Correct index: " << correct_index << ". Got: ";
    int timed_index = timed_ordered_array_search(array, size, needle, res);
    std::cout << timed_index << ". " << (timed_index == correct_index ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!") << '\n';

    return res;
};


int timed_binary_search(int const *const array, int size, int needle, search_result &res) {
    auto start = hrc::now();

    int low = 0, high = size-1;

    while (low <= high) {
        int mid = ((high - low) >> 1) + low;

        if (array[mid] > needle) {
            // what we're searching is to the left of mid
            high = mid - 1;
        } else if (array[mid] < needle){
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
    std::cout << timed_index << ". " << (timed_index == correct_index ? "Correct" : "!!!!!!!!INCORRECT!!!!!!!!") << '\n';

    return res;
};
