#ifndef POINT_H
#define POINT_H

#include <windows.h>

#include "location.h"

extern HDC hDC;

class point : public location {
  public:
    point(const int x, const int y, const COLORREF color = RGB(0, 0, 0))
        : location(x, y), visible(false), color(color) {}
    point(const int x, const int y, const bool visible, const COLORREF color = RGB(0, 0, 0))
        : location(x, y), visible(visible), color(color) {}
    ~point() override;

    [[nodiscard]] bool is_visible() const;

    void draw();
    void erase();
    void move_to(int x, int y);
  protected:
    void virtual _draw();
    void virtual _erase();
  private:
    bool visible;
    COLORREF color;
};

#endif //POINT_H
