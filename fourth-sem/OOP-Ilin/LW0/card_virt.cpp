#include <windows.h>
#include <iostream>
#include <string>
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
using namespace std;
#include "card_virt.h"

extern HDC hdc; // Внешняя переменная контекста устройства

// Конструктор
Card::Card(int InitX, int InitY, string InitRank, string InitSuit, int InitWidth, int InitHeight) 
    : Point(InitX, InitY)
{
    Rank = InitRank;
    Suit = InitSuit;
    Width = InitWidth;
    Height = InitHeight;
}

// Деструктор
Card::~Card()
{
    // Ничего не делает
}

// Функция для конвертации UTF-8 строки в wstring
wstring utf8_to_wstring(const string& str) {
    if (str.empty()) return wstring();
    
    // Вычисляем размер необходимого буфера
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    wstring wstrTo(size_needed, 0);
    
    // Выполняем конвертацию
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

// Отобразить карту (переопределение виртуального метода)
void Card::Show()
{
    Visible = true;
    
    // Создаем перо и кисть
    HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    HBRUSH Brush = CreateSolidBrush(RGB(255, 255, 255));
    
    // Выбираем перо и кисть
    SelectObject(hdc, Pen);
    SelectObject(hdc, Brush);
    
    // Рисуем прямоугольник карты
    Rectangle(hdc, X - Width/2, Y - Height/2, X + Width/2, Y + Height/2);
    
    // Определяем цвет масти
    COLORREF suitColor = RGB(0, 0, 0); // По умолчанию черный
    
    if (Suit == "червы" || Suit == "бубны") {
        suitColor = RGB(255, 0, 0); // Красный для червей и бубнов
    }
    
    // Создаем перо для текста
    HPEN TextPen = CreatePen(PS_SOLID, 1, suitColor);
    SelectObject(hdc, TextPen);
    
    // Устанавливаем цвет текста
    SetTextColor(hdc, suitColor);
    SetBkMode(hdc, TRANSPARENT);
    
    // Правильно конвертируем UTF-8 в широкие символы
    wstring wRank = utf8_to_wstring(Rank);
    wstring wSuit = utf8_to_wstring(Suit);
    
    // Выбираем шрифт для текста
    HFONT hTextFont = CreateFontW(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 
                             DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, 
                             ANTIALIASED_QUALITY, DEFAULT_PITCH, L"Arial");
    HFONT hOldTextFont = (HFONT)SelectObject(hdc, hTextFont);
    
    // Выводим достоинство и масть в верхнем левом углу
    TextOutW(hdc, X - Width/2 + 5, Y - Height/2 + 5, wRank.c_str(), wRank.length());
    TextOutW(hdc, X - Width/2 + 5, Y - Height/2 + 25, wSuit.c_str(), wSuit.length());
    
    // Получаем символ масти
    const wchar_t* suitSymbolChar = L"";
    
    if (Suit == "пики") suitSymbolChar = L"\u2660"; // ♠
    else if (Suit == "червы") suitSymbolChar = L"\u2665"; // ♥
    else if (Suit == "бубны") suitSymbolChar = L"\u2666"; // ♦
    else if (Suit == "трефы") suitSymbolChar = L"\u2663"; // ♣
    
    // Восстанавливаем предыдущий шрифт и освобождаем ресурс
    SelectObject(hdc, hOldTextFont);
    DeleteObject(hTextFont);
    
    // Выбираем шрифт большего размера для символа масти
    HFONT hSymbolFont = CreateFontW(48, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 
                              DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, 
                              ANTIALIASED_QUALITY, DEFAULT_PITCH, L"Arial Unicode MS");
    HFONT hOldSymbolFont = (HFONT)SelectObject(hdc, hSymbolFont);
    
    // Выводим символ в центре
    TextOutW(hdc, X - 12, Y - 24, suitSymbolChar, wcslen(suitSymbolChar));
    
    // Восстанавливаем предыдущий шрифт
    SelectObject(hdc, hOldSymbolFont);
    DeleteObject(hSymbolFont);
    
    // Снова выбираем текстовый шрифт для нижнего угла
    hTextFont = CreateFontW(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 
                     DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, 
                     ANTIALIASED_QUALITY, DEFAULT_PITCH, L"Arial");
    hOldTextFont = (HFONT)SelectObject(hdc, hTextFont);
    
    // Выводим достоинство и масть в нижнем правом углу
    TextOutW(hdc, X + Width/2 - 40, Y + Height/2 - 40, wRank.c_str(), wRank.length());
    TextOutW(hdc, X + Width/2 - 40, Y + Height/2 - 20, wSuit.c_str(), wSuit.length());
    
    // Восстанавливаем предыдущий шрифт
    SelectObject(hdc, hOldTextFont);
    
    // Освобождаем ресурсы
    DeleteObject(hTextFont);
    DeleteObject(Pen);
    DeleteObject(Brush);
    DeleteObject(TextPen);
}

// Скрыть карту (переопределение виртуального метода)
void Card::Hide()
{
    Visible = false;
    
    // Создаем перо и кисть цвета фона консоли
    HPEN Pen = CreatePen(PS_SOLID, 2, RGB(12, 12, 12));
    HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
    
    // Выбираем перо и кисть
    SelectObject(hdc, Pen);
    SelectObject(hdc, Brush);
    
    // Рисуем прямоугольник поверх карты
    Rectangle(hdc, X - Width/2, Y - Height/2, X + Width/2, Y + Height/2);
    
    // Освобождаем ресурсы
    DeleteObject(Pen);
    DeleteObject(Brush);
}

// Перемещение карты (переопределение виртуального метода)
void Card::MoveTo(int NewX, int NewY)
{
    Hide();    // Скрыть карту
    X = NewX;  // Обновить координаты
    Y = NewY;
    Show();    // Показать карту на новом месте
}

// Перетаскивание карты (переопределение виртуального метода)
void Card::Drag(int Step)
{
    int CardX, CardY;
    
    CardX = GetX();
    CardY = GetY();
    
    while (1)
    {
        if (KEY_DOWN(VK_ESCAPE))
        {
            break;
        }
        
        // Диагональное перемещение (улучшенная версия для виртуального метода)
        if (KEY_DOWN(VK_LEFT) && KEY_DOWN(VK_UP))
        {
            CardX -= Step;
            CardY -= Step;
            MoveTo(CardX, CardY);
            Sleep(100);
        }
        else if (KEY_DOWN(VK_LEFT) && KEY_DOWN(VK_DOWN))
        {
            CardX -= Step;
            CardY += Step;
            MoveTo(CardX, CardY);
            Sleep(100);
        }
        else if (KEY_DOWN(VK_RIGHT) && KEY_DOWN(VK_UP))
        {
            CardX += Step;
            CardY -= Step;
            MoveTo(CardX, CardY);
            Sleep(100);
        }
        else if (KEY_DOWN(VK_RIGHT) && KEY_DOWN(VK_DOWN))
        {
            CardX += Step;
            CardY += Step;
            MoveTo(CardX, CardY);
            Sleep(100);
        }
        // Обычное перемещение
        else if (KEY_DOWN(VK_LEFT))
        {
            CardX -= Step;
            MoveTo(CardX, CardY);
            Sleep(100);
        }
        else if (KEY_DOWN(VK_RIGHT))
        {
            CardX += Step;
            MoveTo(CardX, CardY);
            Sleep(100);
        }
        else if (KEY_DOWN(VK_UP))
        {
            CardY -= Step;
            MoveTo(CardX, CardY);
            Sleep(100);
        }
        else if (KEY_DOWN(VK_DOWN))
        {
            CardY += Step;
            MoveTo(CardX, CardY);
            Sleep(100);
        }
    }
} 