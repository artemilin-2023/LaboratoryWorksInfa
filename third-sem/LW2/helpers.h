//
// Created by y7o4ka on 17.10.2024.
//

#ifndef LW_HELPERS_H
#define LW_HELPERS_H

int *generate_array(int length, int min, int max, std::mt19937 &gen);

int *remove_number_from_array(const int *array, int *fixed_array, int length,
                              int number_to_remove, int index_to_remove);

#endif //LW_HELPERS_H
