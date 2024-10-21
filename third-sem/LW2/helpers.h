//
// Created by y7o4ka on 17.10.2024.
//

#ifndef LW_HELPERS_H
#define LW_HELPERS_H

template<class RNG>
int *generate_array(int length, int min, int max, RNG &gen);

int *remove_number_from_array(int *array, int length, int number_to_remove);

#endif //LW_HELPERS_H
