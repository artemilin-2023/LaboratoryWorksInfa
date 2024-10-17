#include "functions.h"
using namespace std;

IntPoint* GenerateArray(int from, int count, IntFunc func) {
    auto* arr = new IntPoint[count];

    int x = from;
    for (int i = 0; i < count; i++) {
        arr[i].x = x;
        arr[i].y = func(x);
        x++;
    }

    return arr;
}

DoublePoint* GenerateArray(double from, int count, double step, DoubleFunc func) {
    auto* arr = new DoublePoint[count];

    double current = from;
    for (int i = 0; i < count; i++) {
        arr[i].x = current;
        arr[i].y = func(current);
        current += step;
    }

    return arr;
}



void WriteArrayToFile(IntPoint* arr, int n, const string& filename) {
    ofstream fout(filename);

    fout << "x y\n";
    for (int i = 0; i < n; i++) {
        fout << arr[i].x << " " << arr[i].y << endl;
    }
    fout.close();
}

void WriteArrayToFile(DoublePoint* arr, int n, const string& filename, int precision) {
    ofstream fout(filename);

    fout << "x y\n";
    for (int i = 0; i < n; i++) {
        fout << setprecision(precision) << arr[i].x << " " << arr[i].y << endl;
    }
    fout.close();
}

string GetFilename() {
    static int index = 0;
    string res = "out" + to_string(index) + ".txt";
    index++;
    return res;
}

double GetAverageExecutionTime(IntFunc func, long long count) {
    const int startX = 0;
    const int repeats = 5; // Количество замеров скорости

    auto* res = new IntPoint[count];
    long long totalTime = 0; // Общее время за 5 замеров


    for (int repeat = 0; repeat < repeats; repeat++) {
        int current = startX;
        auto begin = chrono::steady_clock::now();

        for (long long i = 0; i < count; i++) {
            res[i].x = current;
            res[i].y = func(current);
            current++;
        }
        auto end = chrono::steady_clock::now();
        auto elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - begin);
        totalTime += elapsed_ms.count();
    }

    delete[] res;
    return double(totalTime) / repeats;
}

double GetAverageExecutionTimefordouble(DoubleFunc func, double step, long long count) {
    const double startX = 0;
    const int repeats = 5; // Количество замеров скорости

    auto* res = new DoublePoint[count];
    long long totalTime = 0; // Общее время за 5 замеров


    for (int repeat = 0; repeat < repeats; repeat++) {
        double current = startX;
        auto begin = chrono::steady_clock::now();

        for (long long i = 0; i < count; i++) {
            res[i].x = current;
            res[i].y = func(current);
            current += step;
        }
        auto end = chrono::steady_clock::now();
        auto elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - begin);
        totalTime += elapsed_ms.count();
    }

    delete[] res;
    return double(totalTime) / repeats;
}
