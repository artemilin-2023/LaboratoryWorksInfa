#ifndef LW2_2_POINTERS_HELPERS
#define LW2_2_POINTERS_HELPERS

#include <iostream>

void handle_file(const char* file_name);
int validate_and_read_matrix(std::ifstream& in, int* &matrix, int &height, int &width);
void print_matrix(const int* matrix, int height, int width);

#endif
