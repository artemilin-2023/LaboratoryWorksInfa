#ifndef CHANDELIER_H
#define CHANDELIER_H
#include "point.h"

class chandelier final : point {
  public:
    chandelier(const int x, const int y, const COLORREF color = RGB(0, 0, 0)) : point(x, y, color) {}
    chandelier(const int x, const int y, const bool visible, const COLORREF color = RGB(0, 0, 0))
        : point(x, y, visible, color) {}

  protected:
    void _draw() override;
    void _erase() override;
};



#endif //CHANDELIER_H
