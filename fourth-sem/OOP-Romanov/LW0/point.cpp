#include "point.h"

point::point(const int x, const int y) : location(x, y), visible(false) {}
point::~point() = default;
bool point::is_visible() const { return visible; }
void point::draw() {
    visible = true;
    SetPixel(hdc, x,   y,   RGB(255, 255, 255));
    SetPixel(hdc, x+1, y,   RGB(255, 255, 255));
    SetPixel(hdc, x,   y+1, RGB(255, 255, 255));
    SetPixel(hdc, x+1, y+1, RGB(255, 255, 255));
}
void point::hide() {
    visible = false;
    SetPixel(hdc, x,   y,   RGB(0, 0, 0));
    SetPixel(hdc, x+1, y,   RGB(0, 0, 0));
    SetPixel(hdc, x,   y+1, RGB(0, 0, 0));
    SetPixel(hdc, x+1, y+1, RGB(0, 0, 0));
}
