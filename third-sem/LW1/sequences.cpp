#include <cmath>
#include "sequences.h"

int ordered(int x) {
    return 3 * x + 3;
}

int orderBack(int x) {
    return -3 * x;
}

int randomized(int x) {
    return ((rand() % ((x + 1) * 2)) - x);
}

int saw(int x) {
    return ordered(x % 10);
}

int step(int x) {
    int segment = x / 20;
    return (rand() % 10) + segment * 10;
}

int quasi(int x) {
    int el = ordered(x);
    return rand() % 100 >= 30 ? el : el - ((rand() % 20) + 2);
}

//Double sequences

double ordered(double x) {
    return 3.2 * x + 3;
}

double sinusoid(double x) {
    return sin(x);
}

double orderBack(double x) {
    return -2.7 * x;
}

double randomized(double x) {
    return (rand() % 100) / 100.0;
}

double saw(double x) {
    return (int(x) % 3) + (x - int(x));
}

double step(double x) {
    int segment = int(x) / 2;
    double randFrac = ((rand() % 20) + 1) / 10.0;
    return randFrac + segment * 4 + (x - int(x));
}

double quasi(double x) {
    double el = ordered(x);
    double randFraction = (rand() % 20) / 100.0;
    return ((rand() % 100) >= 15) ? el : el - ((rand() % 20) + 2 + randFraction);
}
