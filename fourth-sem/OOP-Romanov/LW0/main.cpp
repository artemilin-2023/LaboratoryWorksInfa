#include <chrono>
#include <iostream>
#include <thread>

#define WINVER 0x0605
#include <windows.h>

#include "point.h"

#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000)

HWND hWnd;
HDC hDC;

void update_loop(const std::vector<std::unique_ptr<point>>& objects);
void repaint_objects(const std::vector<std::unique_ptr<point>>& objects);

int main() {
    hWnd = GetConsoleWindow();
    if (!hWnd) {
        std::cout << "There is no console window!\n";
        return 1;
    }
    hDC = GetDC(hWnd);
    if (!hDC) {
        std::cout << "There is no device context associated with the console window! (how?!?)\n";
        return 2;
    }
    // let the Windows 11 console update first
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    // create some example objects
    std::vector<std::unique_ptr<point>> vec;
    vec.emplace_back(new point(150, 100, true));
    vec.emplace_back(new point(153, 100, true));

    update_loop(vec);
    repaint_objects(vec);

    ReleaseDC(hWnd, hDC);
    return 0;
}

void update_loop(const std::vector<std::unique_ptr<point>>& objects) {
    int selected_object = 0;
    while (true) {
        if (KEY_DOWN(VK_ESCAPE)) {
            // escape out of the loop
            break;
        }

        // object movement
        if (KEY_DOWN(VK_LEFT)) { // left arrow
            auto &object = objects[selected_object];
            object->move_to(object->get_x()-1, object->get_y());
        }

        if (KEY_DOWN(VK_RIGHT)) // right arrow
        {
            auto &object = objects[selected_object];
            object->move_to(object->get_x()+1, object->get_y());
        }

        if (KEY_DOWN(VK_UP)) // up arrow
        {
            auto &object = objects[selected_object];
            object->move_to(object->get_x(), object->get_y()-1);
        }

        if (KEY_DOWN(VK_DOWN)) // down arrow
        {
            auto &object = objects[selected_object];
            object->move_to(object->get_x(), object->get_y()+1);
        }

        // object selection
        if (KEY_DOWN(0x48)) // `H`
        {
            selected_object = (selected_object + 1) % objects.size();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        if (KEY_DOWN(0x4C)) // `L`
        {
            selected_object = (selected_object - 1) % objects.size();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        // show/hide
        if (KEY_DOWN(VK_SPACE)) // spacebar
        {
            auto &object = objects[selected_object];
            if (object->is_visible()) {
                object->erase();
            } else {
                object->draw();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        repaint_objects(objects);
        std::cout << "\rSelected: " << selected_object;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void repaint_objects(const std::vector<std::unique_ptr<point>>& objects) {
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);

    const int dpi = static_cast<int>(GetDpiForWindow(hWnd));

    clientRect.top = 16;
    clientRect.right = MulDiv(clientRect.right, dpi, 96);
    clientRect.bottom = MulDiv(clientRect.bottom, dpi, 96);

    // Fill with default window background color
    HBRUSH hBrush = CreateSolidBrush(RGB(242, 242, 242));
    FillRect(hDC, &clientRect, hBrush);
    DeleteObject(hBrush);

    for (const auto &object : objects) {
        if (object->is_visible()) {
            object->draw();
        }
    }
}
