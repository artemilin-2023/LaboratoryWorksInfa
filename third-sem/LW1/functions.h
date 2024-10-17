#ifndef LABA_FUNCTIONS_H
#define LABA_FUNCTIONS_H

#include "types.h"
#include <string>
#include <iomanip>
#include <fstream>
#include <chrono>

IntPoint* GenerateArray(int from, int count, IntFunc func); // Функция создание целочисленного массива
DoublePoint* GenerateArray(double from, int count, double step, DoubleFunc func); // Функция создание десятичного массива
void WriteArrayToFile(IntPoint* arr, int n, const std::string& filename); // Функция записи целочисленного массива в файл
void WriteArrayToFile(DoublePoint* arr, int n, const std::string& filename, int precision = 4); // Функция записи десятичного массива в файл
std::string GetFilename(); // Функция получения уникального имени файла
double GetAverageExecutionTime(IntFunc func, long long count); // Функция подсчета среднего времени заполнения целочисленного массива
double GetAverageExecutionTimefordouble(DoubleFunc func, double step, long long count); // Функция подсчета среднего времени заполнения вещественного массива
#endif
