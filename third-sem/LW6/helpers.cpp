#include "helpers.h"

#include <algorithm>

std::vector<int> generate_array(int length, int min, int max) {
    std::vector<int> vec(length);

    int step = (max - min) / length;

    for (int i = 0, num = min; i < length; i++, num += step) {
        vec[i] = num;
    }

    std::shuffle(vec.begin(), vec.end(), std::default_random_engine { std::random_device()() });

    return vec;
}