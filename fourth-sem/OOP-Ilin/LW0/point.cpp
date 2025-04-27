#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
using namespace std;
#include "point.h"

extern HDC hdc; // Внешняя переменная контекста устройства

// Конструктор
Point::Point(int InitX, int InitY) : Location(InitX, InitY)
{
    Visible = false; // Точка не видна
}

// Деструктор
Point::~Point()
{
    // Ничего не делает
}

// Получить видимость точки
bool Point::GetVisible()
{
    return Visible;
}

// Установить видимость точки
void Point::SetVisible(bool NewVisible)
{
    Visible = NewVisible;
}

// Показать точку
void Point::Show()
{
    Visible = true; // Точка видна
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    SetPixel(hdc, X, Y, RGB(255, 0, 0)); // Рисуем красную точку

    // Рисуем 4 точки, чтобы было лучше видно на экране
    SetPixel(hdc, X + 1, Y, RGB(255, 0, 0));
    SetPixel(hdc, X, Y + 1, RGB(255, 0, 0));
    SetPixel(hdc, X + 1, Y + 1, RGB(255, 0, 0));
}

// Скрыть точку
void Point::Hide()
{
    Visible = false; // Точка не видна

    // Рисуем 4 точки черным цветом (цвет фона)
    SetPixel(hdc, X, Y, RGB(0, 0, 0));
    SetPixel(hdc, X + 1, Y, RGB(0, 0, 0));
    SetPixel(hdc, X, Y + 1, RGB(0, 0, 0));
    SetPixel(hdc, X + 1, Y + 1, RGB(0, 0, 0));
}

// Перемещение точки на новые координаты
void Point::MoveTo(int NewX, int NewY)
{
    Hide();     // Скрыть точку на текущей позиции
    X = NewX;   // Обновить координаты
    Y = NewY;
    Show();     // Показать точку на новой позиции
}

// Перетаскивание точки с помощью клавиш управления
void Point::Drag(int Step)
{
    int PointX, PointY; // Координаты точки
    
    PointX = GetX(); // Получаем начальные координаты
    PointY = GetY();

    while (1) { // Бесконечный цикл управления
        if (KEY_DOWN(VK_ESCAPE)) {
            break; // Выход по Escape
        }

        if (KEY_DOWN(VK_LEFT)) { // Стрелка влево
            PointX -= Step;
            MoveTo(PointX, PointY);
            Sleep(500);
        }

        if (KEY_DOWN(VK_RIGHT)) { // Стрелка вправо
            PointX += Step;
            MoveTo(PointX, PointY);
            Sleep(500);
        }

        if (KEY_DOWN(VK_UP)) { // Стрелка вверх
            PointY -= Step;
            MoveTo(PointX, PointY);
            Sleep(500);
        }

        if (KEY_DOWN(VK_DOWN)) { // Стрелка вниз
            PointY += Step;
            MoveTo(PointX, PointY);
            Sleep(500);
        }
    }
} 