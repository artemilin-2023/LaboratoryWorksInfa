#ifndef LW2_2_ARRAYS_HELPERS
#define LW2_2_ARRAYS_HELPERS

#include <iostream>

// reads the file and sets the matrix data. returns an error code
int read_file(const char* file_name, int** &matrix, int &height, int &width);
// processes the matrix using functions from the lw
void process_matrix(int** matrix, int height, int width);
// initializes matrix, then validates and reads a matrix from an ifstream. returns an error code
int validate_and_read_matrix(std::ifstream& in, int** &matrix, int &height, int &width);
// prints a matrix
void print_matrix(int const *const *matrix, int height, int width);

#endif
