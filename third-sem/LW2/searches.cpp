//
// Created by y7o4ka on 17.10.2024.
//

#include <memory>
#include "searches.h"


using hrc = std::chrono::high_resolution_clock;


auto timed_better_linear_search(int const *const array, int size, int needle) {
    auto start = hrc::now();

    for (int i = 0; i < size; ++i) {
        if (array[i] == needle)
            // found
            return hrc::now() - start;
    }
    // not found
    return hrc::now() - start;
}

long counted_better_linear_search(int const *const array, int size, int needle) {
    long comparison_count = 0;

    for (int i = 0; i < size; ++i) {
        comparison_count++;
        if (array[i] == needle)
            // found
            return comparison_count;
    }
    // not found
    return comparison_count;
}

search_result better_linear_search(int const *const array, int size, int needle) {
    return {timed_better_linear_search(array, size, needle),
            counted_better_linear_search(array, size, needle)};
};


auto timed_sentinel_linear_search(int const *const array, int size, int needle) {
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

    if((i < size-1) || (temp_array[size-1] == needle))
        // found
        return hrc::now()-start;
    //not found
    return hrc::now()-start;
}

long counted_sentinel_linear_search(int const *const array, int size, int needle) {
    std::unique_ptr<int[]> temp_array(new int[size]);
    std::copy(array, array + size, temp_array.get());

    long comparison_count = 0;

    int last = temp_array[size-1];
    temp_array[size-1] = needle;

    int i = 0;
    while(temp_array[i] != needle) {
        ++comparison_count;
        ++i;
    }

    temp_array[size-1] = last;

    ++comparison_count; // check the last element
    if((i < size-1) || (temp_array[size-1] == needle))
        // found
        return comparison_count;
    //not found
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

    int low = 0, high = size-1;

    while (low <= high) {
        int mid = ((high - low) >> 1) + low;

        if (array[mid] > needle) {
            // what we're searching is to the left of mid
            high = mid - 1;
        } else if (array[mid] < needle){
            // to the right of mid
            low = mid+1;
        } else {
            // found
            return hrc::now()-start;
        }
    }
    // not found
    return hrc::now()-start;
}

search_result binary_search(int const *const array, int size, int needle) {
    return {timed_binary_search(array, size, needle), 0};
};
