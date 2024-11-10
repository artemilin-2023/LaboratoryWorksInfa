#include <iostream>
#include <fstream>

using namespace std;

int read_matrix(const char* file_name, int** &matrix, int& n, int& m);
void print_matrix(int** matrix, int n, int m);
pair<int*, int*> find_min_max(int** matrix, int n, int m);
void swap(int* a, int* b);

// const char* PATH_TO_MATRIX = "matrix.txt";
const char* PATH_TO_MATRIX = "matrix-2.txt";

int main()
{
	int n, m;
	int **matrix;
	int result_code = read_matrix(PATH_TO_MATRIX, matrix, n, m);
    if (result_code != 0)
	{
		cout << "Произошла ошибка со статус кодом: " << result_code;
		return result_code;
	}

	cout << "Исходная матрица: " << '\n';
	print_matrix(matrix, n, m);

	auto min_max = find_min_max(matrix, n, m);
    swap(min_max.first, min_max.second);
	cout << "Результат работы: " << '\n';
	print_matrix(matrix, n, m);

}

void swap(int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

int read_matrix(const char* file_name, int** &matrix, int& n, int& m) {
	ifstream input(file_name);
    if (!input)
		return 1;

    input >> n >> m;
	cout << "n: " << n << " m: " << m << '\n';
    if (input.fail())
    	return 2;
    if (n <= 0)
		return 3;
   	if (m <= 0)
		return 4;

	matrix = new int* [n];
    for (int i = 0; i < n; i++)
	{
		matrix[i] = new int[m];
    	for (int j = 0; j < m; j++)
		{
			input >> matrix[i][j];
          	if (input.fail())
				return 2;
		}
        cout << '\n';
    }

	return 0;
}

void print_matrix(int** matrix, int n, int m) {
	for (int i = 0; i < n; i++)
	{
    	for (int j = 0; j < m; j++)
		{
        	cout << matrix[i][j] << ' ';
        }
       	cout << '\n';
   	}
}

pair<int*, int*> find_min_max(int** matrix, int n, int m) {
	int min_i = 0;
	int min_j = 0;
	int max_i = 0;
	int max_j = 0;
	int *min = &matrix[0][0];
	int *max = &matrix[0][0];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (matrix[i][j] > *max)
			{
				max_i = i;
				max_j = j;
				max = &matrix[i][j];
			}
			if (matrix[i][j] < *min)
			{
				min_i = i;
				min_j = j;
				min = &matrix[i][j];
			}
		}
	}

	cout << "min element matrix[" << min_i << "][" << min_j << "] = " << *min << '\n';
	cout << "max element matrix[" << max_i << "][" << max_j << "] = " << *max << '\n';

	return make_pair(min, max);
}
