#include <windows.h>
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
using std::cout;
using std::endl;
using std::string;
using std::wstring;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
#include "card_virt.h"

extern HDC hdc; // Внешняя переменная контекста устройства

// Реализация Card
Card::Card(int InitX, int InitY, string InitRank, string InitSuit, int InitWidth, int InitHeight) 
    : Point(InitX, InitY) {
    Rank = InitRank;
    Suit = InitSuit;
    Width = InitWidth;
    Height = InitHeight;
    IsFaceUp = false;
    ChangeHitbox();
}

Card::~Card() {
}

void Card::ChangeHitbox() {
    leftBorder = X - Width/2;
    rightBorder = X + Width/2;
    topBorder = Y - Height/2;
    bottomBorder = Y + Height/2;
}

void Card::MoveTo(int NewX, int NewY) {
    Hide();
    X = NewX;
    Y = NewY;
    ChangeHitbox();
    Show();
}

// Реализация HeartsCard
HeartsCard::HeartsCard(int InitX, int InitY, string InitRank) 
    : Card(InitX, InitY, InitRank, "червы", 100, 150) {
}

HeartsCard::~HeartsCard() {
}

// Реализация ClubsCard
ClubsCard::ClubsCard(int InitX, int InitY, string InitRank) 
    : Card(InitX, InitY, InitRank, "трефы", 100, 150) {
}

ClubsCard::~ClubsCard() {
}

// Реализация ConflictObject
ConflictObject::ConflictObject(int InitX, int InitY, int InitWidth, int InitHeight) 
    : Point(InitX, InitY) {
    Width = InitWidth;
    Height = InitHeight;
    ChangeHitbox();
}

ConflictObject::~ConflictObject() {
}

// Реализация CardShuffler
CardShuffler::CardShuffler(int InitX, int InitY) 
    : ConflictObject(InitX, InitY, 100, 100) {
}

CardShuffler::~CardShuffler() {
}

// Реализация CardDealer
CardDealer::CardDealer(int InitX, int InitY) 
    : ConflictObject(InitX, InitY, 100, 100) {
}

CardDealer::~CardDealer() {
}

// Функция для конвертации UTF-8 строки в wstring
wstring utf8_to_wstring(const string& str) {
    if (str.empty()) return wstring();
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

// Показать карту
void Card::Show() {
    Visible = true;
    
    // Создаем перо и кисть
    HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    HBRUSH Brush = CreateSolidBrush(RGB(255, 255, 255));
    
    // Выбираем перо и кисть
    SelectObject(hdc, Pen);
    SelectObject(hdc, Brush);
    
    // Рисуем прямоугольник карты
    Rectangle(hdc, X - Width/2, Y - Height/2, X + Width/2, Y + Height/2);
    
    if (IsFaceUp) {
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
        
        // Конвертируем UTF-8 в широкие символы
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
        DeleteObject(TextPen);
    } else {
        // Рисуем рубашку карты
        HPEN BackPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        HBRUSH BackBrush = CreateSolidBrush(RGB(0, 0, 255));
        SelectObject(hdc, BackPen);
        SelectObject(hdc, BackBrush);
        
        // Рисуем узор на рубашке
        for (int i = 0; i < Width; i += 10) {
            for (int j = 0; j < Height; j += 10) {
                if ((i + j) % 20 == 0) {
                    Rectangle(hdc, X - Width/2 + i, Y - Height/2 + j, 
                             X - Width/2 + i + 10, Y - Height/2 + j + 10);
                }
            }
        }
        
        DeleteObject(BackPen);
        DeleteObject(BackBrush);
    }
    
    // Освобождаем ресурсы
    DeleteObject(Pen);
    DeleteObject(Brush);
}

// Скрыть карту
void Card::Hide() {
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

// Перевернуть карту
void Card::Flip() {
    IsFaceUp = !IsFaceUp;
    Show();
}

// Взаимодействие с другой картой
void Card::Interact(Card* other) {
    // Базовая реализация - просто переворачиваем обе карты
    Flip();
    other->Flip();
}

// Показать карту червей
void HeartsCard::Show() {
    // Сначала вызываем базовую реализацию
    Card::Show();
    
    if (IsFaceUp) {
        // Добавляем специальные эффекты для червей
        HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
        SelectObject(hdc, Pen);
        
        // Рисуем дополнительные сердечки по углам
        const wchar_t* heartSymbol = L"\u2665";
        HFONT hFont = CreateFontW(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 
                             DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, 
                             ANTIALIASED_QUALITY, DEFAULT_PITCH, L"Arial Unicode MS");
        HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
        
        // Рисуем сердечки в углах
        TextOutW(hdc, X - Width/2 + 10, Y - Height/2 + 10, heartSymbol, 1);
        TextOutW(hdc, X + Width/2 - 20, Y - Height/2 + 10, heartSymbol, 1);
        TextOutW(hdc, X - Width/2 + 10, Y + Height/2 - 20, heartSymbol, 1);
        TextOutW(hdc, X + Width/2 - 20, Y + Height/2 - 20, heartSymbol, 1);
        
        // Восстанавливаем шрифт
        SelectObject(hdc, hOldFont);
        DeleteObject(hFont);
        DeleteObject(Pen);
    }
}

// Взаимодействие с другой картой (для червей)
void HeartsCard::Interact(Card* other) {
    // Если другая карта тоже черви, они "сливаются" в одно большое сердце
    if (other->GetSuit() == "червы") {
        // Создаем большое сердце
        HPEN Pen = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
        SelectObject(hdc, Pen);
        
        const wchar_t* bigHeart = L"\u2665";
        HFONT hFont = CreateFontW(72, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, 
                             DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, 
                             ANTIALIASED_QUALITY, DEFAULT_PITCH, L"Arial Unicode MS");
        HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
        
        // Рисуем большое сердце между картами
        int centerX = (X + other->GetX()) / 2;
        int centerY = (Y + other->GetY()) / 2;
        TextOutW(hdc, centerX - 36, centerY - 36, bigHeart, 1);
        
        // Восстанавливаем шрифт
        SelectObject(hdc, hOldFont);
        DeleteObject(hFont);
        DeleteObject(Pen);
        
        Sleep(1000); // Показываем эффект 1 секунду
    }
    
    // Вызываем базовую реализацию
    Card::Interact(other);
}

// Показать карту треф
void ClubsCard::Show() {
    // Сначала вызываем базовую реализацию
    Card::Show();
    
    if (IsFaceUp) {
        // Добавляем специальные эффекты для треф
        HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        SelectObject(hdc, Pen);
        
        // Рисуем дополнительные трефы по углам
        const wchar_t* clubSymbol = L"\u2663";
        HFONT hFont = CreateFontW(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 
                             DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, 
                             ANTIALIASED_QUALITY, DEFAULT_PITCH, L"Arial Unicode MS");
        HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
        
        // Рисуем трефы в углах
        TextOutW(hdc, X - Width/2 + 10, Y - Height/2 + 10, clubSymbol, 1);
        TextOutW(hdc, X + Width/2 - 20, Y - Height/2 + 10, clubSymbol, 1);
        TextOutW(hdc, X - Width/2 + 10, Y + Height/2 - 20, clubSymbol, 1);
        TextOutW(hdc, X + Width/2 - 20, Y + Height/2 - 20, clubSymbol, 1);
        
        // Восстанавливаем шрифт
        SelectObject(hdc, hOldFont);
        DeleteObject(hFont);
        DeleteObject(Pen);
    }
}

// Взаимодействие с другой картой (для треф)
void ClubsCard::Interact(Card* other) {
    // Если другая карта тоже трефы, они создают "щит"
    if (other->GetSuit() == "трефы") {
        // Создаем щит из треф
        HPEN Pen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
        SelectObject(hdc, Pen);
        
        const wchar_t* shieldClub = L"\u2663";
        HFONT hFont = CreateFontW(72, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, 
                             DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, 
                             ANTIALIASED_QUALITY, DEFAULT_PITCH, L"Arial Unicode MS");
        HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
        
        // Рисуем щит между картами
        int centerX = (X + other->GetX()) / 2;
        int centerY = (Y + other->GetY()) / 2;
        
        // Рисуем круг щита
        Ellipse(hdc, centerX - 50, centerY - 50, centerX + 50, centerY + 50);
        
        // Рисуем трефу в центре щита
        TextOutW(hdc, centerX - 36, centerY - 36, shieldClub, 1);
        
        // Восстанавливаем шрифт
        SelectObject(hdc, hOldFont);
        DeleteObject(hFont);
        DeleteObject(Pen);
        
        Sleep(1000); // Показываем эффект 1 секунду
    }
    
    // Вызываем базовую реализацию
    Card::Interact(other);
}

// Показать перемешиватель карт
void CardShuffler::Show() {
    Visible = true;
    
    // Создаем перо и кисть
    HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    HBRUSH Brush = CreateSolidBrush(RGB(150, 150, 150));
    
    // Выбираем перо и кисть
    SelectObject(hdc, Pen);
    SelectObject(hdc, Brush);
    
    // Рисуем прямоугольник
    Rectangle(hdc, X - Width/2, Y - Height/2, X + Width/2, Y + Height/2);
    
    const wchar_t* shuffleText = L"Shuffler";
    HFONT hFont = CreateFontW(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 
                         DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, 
                         ANTIALIASED_QUALITY, DEFAULT_PITCH, L"Arial");
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
    
    // Выводим текст в центре
    TextOutW(hdc, X - 50, Y - 10, shuffleText, wcslen(shuffleText));
    
    // Восстанавливаем шрифт
    SelectObject(hdc, hOldFont);
    DeleteObject(hFont);
    
    // Освобождаем ресурсы
    DeleteObject(Pen);
    DeleteObject(Brush);
}

// Взаимодействие с картой (для перемешивателя)
void CardShuffler::Interact(Card* card) {
    // Случайно перемещаем карту
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> disX(X - Width/2, X + Width/2);
    uniform_int_distribution<> disY(Y - Height/2, Y + Height/2);
    
    card->MoveTo(disX(gen), disY(gen));
    card->Flip(); // Переворачиваем карту
}

// Показать раздающего карты
void CardDealer::Show() {
    Visible = true;
    
    // Создаем перо и кисть
    HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    HBRUSH Brush = CreateSolidBrush(RGB(200, 200, 200));
    
    // Выбираем перо и кисть
    SelectObject(hdc, Pen);
    SelectObject(hdc, Brush);
    
    // Рисуем прямоугольник
    Rectangle(hdc, X - Width/2, Y - Height/2, X + Width/2, Y + Height/2);
    
    const wchar_t* dealText = L"Dealer";
    HFONT hFont = CreateFontW(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 
                         DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, 
                         ANTIALIASED_QUALITY, DEFAULT_PITCH, L"Arial");
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
    
    // Выводим текст в центре
    TextOutW(hdc, X - 40, Y - 10, dealText, wcslen(dealText));
    
    // Восстанавливаем шрифт
    SelectObject(hdc, hOldFont);
    DeleteObject(hFont);
    
    // Освобождаем ресурсы
    DeleteObject(Pen);
    DeleteObject(Brush);
}

// Взаимодействие с картой (для раздающего)
void CardDealer::Interact(Card* card) {
    // Раздаем карту в определенную позицию
    static int dealX = X + 150;
    static int dealY = Y;
    
    card->MoveTo(dealX, dealY);
    card->SetIsFaceUp(false);
    card->Show();
    
    // Обновляем позицию для следующей карты
    dealX += 30;
    if (dealX > X + 300) {
        dealX = X + 150;
        dealY += 50;
    }
}

// Реализация ConflictObject
void ConflictObject::Show()
{
    Visible = true;
    
    // Создаем перо и кисть
    HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    HBRUSH Brush = CreateSolidBrush(RGB(150, 150, 150));
    
    // Выбираем перо и кисть
    SelectObject(hdc, Pen);
    SelectObject(hdc, Brush);
    
    // Рисуем прямоугольник
    Rectangle(hdc, X - Width/2, Y - Height/2, X + Width/2, Y + Height/2);
    
    // Освобождаем ресурсы
    DeleteObject(Pen);
    DeleteObject(Brush);
}

void ConflictObject::Hide()
{
    Visible = false;
    
    // Создаем перо и кисть цвета фона
    HPEN Pen = CreatePen(PS_SOLID, 2, RGB(12, 12, 12));
    HBRUSH Brush = CreateSolidBrush(RGB(12, 12, 12));
    
    // Выбираем перо и кисть
    SelectObject(hdc, Pen);
    SelectObject(hdc, Brush);
    
    // Рисуем прямоугольник поверх объекта
    Rectangle(hdc, X - Width/2, Y - Height/2, X + Width/2, Y + Height/2);
    
    // Освобождаем ресурсы
    DeleteObject(Pen);
    DeleteObject(Brush);
}

void ConflictObject::ChangeHitbox()
{
    leftBorder = X - Width/2;
    rightBorder = X + Width/2;
    topBorder = Y - Height/2;
    bottomBorder = Y + Height/2;
} 