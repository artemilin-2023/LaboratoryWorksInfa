#include "point.h"

point::point(const int x, const int y, const COLORREF color) : location(x, y), visible(false), color(color) {}
point::point(const int x, const int y, const bool visible, const COLORREF color) : location(x, y), visible(visible), color(color) {}
point::~point() {
    if (is_visible()) {
        erase();
    }
}
bool point::is_visible() const { return visible; }
void point::draw() {
    visible = true;
    SetPixel(hDC, x,   y,   color);
    SetPixel(hDC, x+1, y,   color);
    SetPixel(hDC, x,   y+1, color);
    SetPixel(hDC, x+1, y+1, color);
}
void point::erase() {
    visible = false;
    SetPixel(hDC, x,   y,   RGB(242, 242, 242));
    SetPixel(hDC, x+1, y,   RGB(242, 242, 242));
    SetPixel(hDC, x,   y+1, RGB(242, 242, 242));
    SetPixel(hDC, x+1, y+1, RGB(242, 242, 242));
}
void point::move_to(const int x, const int y) {
    bool was_visible = is_visible();
    if (was_visible)
        erase();
    set_x(x);
    set_y(y);
    if (was_visible)
        draw();
}
