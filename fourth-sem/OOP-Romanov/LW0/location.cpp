#include "location.h"

location::location(const int x, const int y) : x(x), y(y) {}
location::~location() = default;
int location::get_x() const { return x; }
int location::get_y() const { return y; }
void location::move_to(const int x, const int y) {
    this->x = x;
    this->y = y;
}
