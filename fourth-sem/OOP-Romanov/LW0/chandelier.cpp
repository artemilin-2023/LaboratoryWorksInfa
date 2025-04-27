#include "chandelier.h"
void chandelier::_draw() {
    // save old pen and brush
    const auto oldPen = static_cast<HPEN>(SelectObject(hdc, GetStockObject(DC_PEN)));
    const auto oldBrush = static_cast<HBRUSH>(SelectObject(hdc, GetStockObject(DC_BRUSH)));

    // width: 200px
    // height: 130px

    // power cord
    HPEN hPen = CreatePen(PS_SOLID, 3, RGB(100, 100, 100));
    SelectObject(hdc, hPen);
    MoveToEx(hdc, x + 100, y, NULL);
    LineTo(hdc, x + 100, y + 50);     // длина крюка 50px
    DeleteObject(hPen);

    // main platform
    hPen = CreatePen(PS_SOLID, 2, RGB(150, 100, 50));
    SelectObject(hdc, hPen);
    HBRUSH hBrush = CreateSolidBrush(RGB(200, 150, 100));
    SelectObject(hdc, hBrush);
    Ellipse(hdc, x, y + 50, x + 200, y + 100);  // платформа 200x50px
    DeleteObject(hPen);
    DeleteObject(hBrush);

    // light bulbs
    hPen = CreatePen(PS_SOLID, 1, RGB(80, 80, 80));
    SelectObject(hdc, hPen);
    hBrush = CreateSolidBrush(RGB(255, 255, 200)); // цвет лампочек
    SelectObject(hdc, hBrush);

    // left bulb
    Ellipse(hdc, x + 40, y + 80, x + 60, y + 130);
    MoveToEx(hdc, x + 50, y + 80, NULL);
    LineTo(hdc, x + 50, y + 130);
    LineTo(hdc, x + 100, y + 75);

    // right bulb
    Ellipse(hdc, x + 140, y + 80, x + 160, y + 130);
    MoveToEx(hdc, x + 150, y + 80, NULL);
    LineTo(hdc, x + 150, y + 130);
    LineTo(hdc, x + 100, y + 75);

    DeleteObject(hPen);
    DeleteObject(hBrush);

    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
}
void chandelier::_erase() { point::_erase(); }
