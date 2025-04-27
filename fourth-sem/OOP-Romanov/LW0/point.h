#ifndef POINT_H
#define POINT_H

#include <windows.h>

#include "location.h"

extern HDC hdc;

class point : location {
public:
    point(int x, int y);
    ~point();

    [[nodiscard]] bool is_visible() const;

    void draw();
    void hide();
    void move_to(int x, int y);
protected:
    bool visible;
};

#endif //POINT_H
