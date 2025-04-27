#ifndef POINT_H
#define POINT_H

#include <windows.h>

#include "location.h"

extern HDC hDC;

class point : public location {
  public:
    point(int x, int y, COLORREF color = RGB(0, 0, 0));
    point(int x, int y, bool visible, COLORREF color = RGB(0, 0, 0));
    ~point();

    [[nodiscard]] bool is_visible() const;

    void draw();
    void erase();
    void move_to(int x, int y);
  protected:
    bool visible;
    COLORREF color;
};

#endif //POINT_H
