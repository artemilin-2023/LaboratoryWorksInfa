#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#define WINVER 0x0605
// #include <windows.h>

#include "point.h"
#include "chandelier.h"

#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000)

HWND hwnd_console; // console window handle
HDC hdc_console; // console window device
HDC hdc; // device context to draw on without flickering the main one
HBITMAP hbm; // buffered bitmap to draw without flickering the main one

void update_loop(const std::vector<std::unique_ptr<point>>& objects);
void repaint_objects(const std::vector<std::unique_ptr<point>>& objects);

int init_buffered_drawing() {
    hwnd_console = GetConsoleWindow();
    if (!hwnd_console) {
        std::cout << "There is no console window!\n";
        return 1;
    }
    hdc_console = GetDC(hwnd_console);
    if (!hdc_console) {
        std::cout << "There is no device context associated with the console window! (how?!?)\n";
        return 2;
    }

    RECT rect;
    GetClientRect(hwnd_console, &rect);
    const int dpi = static_cast<int>(GetDpiForWindow(hwnd_console));
    rect.right = MulDiv(rect.right, dpi, 96);
    rect.bottom = MulDiv(rect.bottom, dpi, 96);

    // get a device and create a bitmap that resembles the main one
    hdc = CreateCompatibleDC(hdc_console);
    hbm = CreateCompatibleBitmap(hdc_console, rect.right, rect.bottom);
    SelectObject(hdc, hbm);
    return 0;
}

void cleanup_drawing() {
    // delete all the things we created
    if (hdc) DeleteDC(hdc);
    if (hbm) DeleteObject(hbm);
    if (hdc_console) ReleaseDC(hwnd_console, hdc_console);
}

int main() {
    if (const int return_code = init_buffered_drawing())
        return return_code;
    // let the Windows 11 console update first
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    // create some example objects
    std::vector<std::unique_ptr<point>> vec;
    vec.emplace_back(new point(150, 100, true));
    vec.emplace_back(new point(153, 100, true, RGB(255, 0, 0)));
    vec.emplace_back(new chandelier(153, 100, true, RGB(200, 150, 100)));
    vec.emplace_back(new chandelier(400, 100, true, RGB(200, 150, 100)));

    // loop that handles keypresses and object manipulation
    update_loop(vec);
    // repaint_objects(vec);

    // release all created resources
    cleanup_drawing();
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
            int size = objects.size();
            selected_object = ((selected_object - 1) % size + size) % size; // positive modulo
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        if (KEY_DOWN(0x4C)) // `L`
        {
            selected_object = (selected_object + 1) % objects.size();
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
        std::cout << "\rSelected: " << selected_object << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void repaint_objects(const std::vector<std::unique_ptr<point>>& objects) {
    RECT clientRect;
    GetClientRect(hwnd_console, &clientRect);

    const int dpi = static_cast<int>(GetDpiForWindow(hwnd_console));

    clientRect.right = MulDiv(clientRect.right, dpi, 96);
    clientRect.bottom = MulDiv(clientRect.bottom, dpi, 96);

    // fill with default window background color
    HBRUSH hBrush = CreateSolidBrush(RGB(242, 242, 242));
    FillRect(hdc, &clientRect, hBrush);
    DeleteObject(hBrush);

    // draw all the objects
    for (const auto &object : objects) {
        if (object->is_visible()) {
            object->draw();
        }
    }

    // copy the drawn bitmap into the console, skipping the first line
    BitBlt(hdc_console,       // Target (screen)
           0, 20,              // Destination (x,y)
           clientRect.right,  // Width
           clientRect.bottom-20, // Height
           hdc,               // Source (buffer)
           0, 0,              // Source (x,y)
           SRCCOPY            // Copy directly
    );
}
