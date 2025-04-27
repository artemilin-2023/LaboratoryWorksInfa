#include "location.h"

location::location(const int x, const int y) : x(x), y(y) {}
location::~location() = default;
int location::get_x() const { return x; }
int location::get_y() const { return y; }
void location::set_x(const int x) {
    this->x = x;
}
void location::set_y(const int y) {
    this->y = y;
}
