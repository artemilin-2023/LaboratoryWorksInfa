#include "point.h"

point::~point() {
    if (is_visible()) {
        erase();
    }
    location::~location();
}
bool point::is_visible() const { return visible; }
void point::draw() {
    visible = true;
    _draw();
}
void point::erase() {
    visible = false;
    _erase();
}
void point::move_to(const int x, const int y) {
    if (is_visible())
        _erase();
    set_x(x);
    set_y(y);
    if (is_visible())
        _draw();
}
void point::_draw() {
    SetPixel(hDC, x,   y,   color);
    SetPixel(hDC, x+1, y,   color);
    SetPixel(hDC, x,   y+1, color);
    SetPixel(hDC, x+1, y+1, color);
}
void point::_erase() {
    SetPixel(hDC, x,   y,   RGB(242, 242, 242));
    SetPixel(hDC, x+1, y,   RGB(242, 242, 242));
    SetPixel(hDC, x,   y+1, RGB(242, 242, 242));
    SetPixel(hDC, x+1, y+1, RGB(242, 242, 242));
}
