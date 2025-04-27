#include <windows.h>
#include <iostream>
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
using namespace std;
#include "card_virt.h"

HDC hdc; // Дескриптор контекста устройства

int main()
{
    // Установка кодовой страницы UTF-8 для консоли
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    // Получение дескриптора консольного окна
    HWND hwnd = GetConsoleWindow();

    // Если дескриптор не существует
    if (hwnd == NULL)
    {
        cout << "Дескриптор консольного окна НЕ НАЙДЕН!\n";
        return 1; // Ошибка
    }

    // Получаем контекст устройства для консольного окна
    hdc = GetWindowDC(hwnd);

    // Если контекст не существует
    if (hdc == 0)
    {
        cout << "Контекст устройства НЕ НАЙДЕН!\n";
        return 2;
    }
    
    // Установка шрифта для консоли (чтобы улучшить отображение)
    HFONT hFont = CreateFontW(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                           DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                           DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Consolas");
    SelectObject(hdc, hFont);

    // Демонстрация иерархии классов Location -> Point -> Card
    int x0 = 300, y0 = 200;
    int i;

    // Создаем точку
    Point point(x0, y0);
    point.Show();
    getchar();

    // Создаем карту (наследник точки)
    Card card(x0 + 200, y0, "Туз", "трефы", 150, 300);
    card.Show();
    getchar();

    // Демонстрация метода Drag (перетаскивание)
    point.Drag(10);
    getchar();

    card.Drag(10);
    getchar();

    // Перемещение объектов
    for (i = 0; i < 5; i++)
    {
        point.MoveTo(x0, y0 + 50 * i);
        card.MoveTo(x0 + 200, y0 + 50 * i);
        Sleep(500);
    }
    getchar();

    // Анимация движения
    while (!KEY_DOWN(VK_ESCAPE))
    {
        for (i = 0; i < 200; i += 5)
        {
            point.MoveTo(x0 + i, y0 + 100);
            card.MoveTo(x0 + 200 + i, y0 + 100);
            Sleep(50);
            
            if (KEY_DOWN(VK_ESCAPE)) break;
        }
        
        for (i = 200; i > 0; i -= 5)
        {
            point.MoveTo(x0 + i, y0 + 100);
            card.MoveTo(x0 + 200 + i, y0 + 100);
            Sleep(50);
            
            if (KEY_DOWN(VK_ESCAPE)) break;
        }
    }
    
    // Освобождаем ресурсы
    DeleteObject(hFont);

    return 0;
} 