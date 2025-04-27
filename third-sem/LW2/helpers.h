//
// Created by y7o4ka on 17.10.2024.
//

#ifndef LW_HELPERS_H
#define LW_HELPERS_H

#include "types.h"
#include "indented_helpers.h"
#include <iostream>
#include <random>
#include <functional>

int *generate_array(int length, int min, int max, std::mt19937 &gen);

int *remove_number_from_array(const int *array, int *fixed_array, int length,
                              int number_to_remove, int index_to_remove);

auto inline is_correct_text(bool p) {
    if (p)
        return "Correct";
    return "\33[31m" "!!!!INCORRECT!!!!" "\33[m";
}

template <typename F>
inline void print_search_result(const std::string &sort_name, F&& f, int correct_index) {
    std::cout << m::print_indent << "Starting " << sort_name << ". Correct index: " << correct_index << ". Got: ";
    int timed_index = f();
    std::cout << timed_index << ". " << is_correct_text(timed_index == correct_index) << '\n';
}

#endif //LW_HELPERS_H
