#include "tasks.h"

#include <limits>

int mult_neg_elems_above_diag(int const *const *matrix, int height, int width) {
    bool neg_found = false;
    int mult = 1;
    for(int i = 0; i < height; i++) {
        for(int j = i + 1; j < width; j++) {
            if(matrix[i][j] < 0) {
                neg_found = true;
                mult *= matrix[i][j];
            }
        }
    }
    if(!neg_found)
        return 0;
    return mult;
}

int min_uneven_elems(int const *const *matrix, int height, int width) {
    bool uneven_found = false;
    int min = std::numeric_limits<int>::max();
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(matrix[i][j] % 2 != 0) {
                uneven_found = true;
                min = matrix[i][j] < min ? matrix[i][j] : min;
            }
        }
    }
    if(!uneven_found)
        return 0;
    return min;
}
