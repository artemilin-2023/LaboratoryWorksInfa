#include <windows.h>
#include <iostream>
#include <chrono>
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
using std::cout;
using std::endl;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
#include "card_virt.h"

HDC hdc; // Дескриптор контекста устройства

// Ограничение на количество взаимодействий в секунду
const int INTERACTIONS_PER_SECOND = 2;
const int INTERACTION_INTERVAL = 1000 / INTERACTIONS_PER_SECOND;

void CheckCollisions(Card* card1, Card* card2, ConflictObject* shuffler, ConflictObject* dealer)
{
    static auto lastInteractionTime = steady_clock::now();
    auto currentTime = steady_clock::now();
    
    // Проверяем, прошло ли достаточно времени с последнего взаимодействия
    if (duration_cast<milliseconds>(currentTime - lastInteractionTime).count() < INTERACTION_INTERVAL) {
        return;
    }
    
    if (card1->IsColliding(card2)) {
        card1->Interact(card2);
        lastInteractionTime = currentTime;
    }
    if (card1->IsColliding(shuffler)) {
        shuffler->Interact(card1);
        lastInteractionTime = currentTime;
    }
    if (card1->IsColliding(dealer)) {
        dealer->Interact(card1);
        lastInteractionTime = currentTime;
    }
    if (card2->IsColliding(shuffler)) {
        shuffler->Interact(card2);
        lastInteractionTime = currentTime;
    }
    if (card2->IsColliding(dealer)) {
        dealer->Interact(card2);
        lastInteractionTime = currentTime;
    }
}

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
    
    // Установка шрифта для консоли
    HFONT hFont = CreateFontW(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                           DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                           DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Consolas");
    SelectObject(hdc, hFont);

    // Создаем карты разных мастей
    HeartsCard heartsCard(300, 200, "Туз");
    ClubsCard clubsCard(500, 200, "Король");
    
    // Создаем объекты взаимодействия
    CardShuffler shuffler(400, 400);
    CardDealer dealer(600, 400);
    
    cout << "Демонстрация работы с картами:\n";
    cout << "1. Используйте стрелки для перемещения карт\n";
    cout << "2. При пересечении карт или объектов произойдет взаимодействие\n";
    cout << "3. Нажмите ESC для выхода\n";
    
    // Показываем все объекты
    heartsCard.Show();
    clubsCard.Show();
    shuffler.Show();
    dealer.Show();

    
    heartsCard.Show();
    clubsCard.Show();
    shuffler.Show();
    dealer.Show();
    
    while (true) {
        if (KEY_DOWN(VK_ESCAPE)) {
            break;
        }

        // Перемещение первой карты
        if (KEY_DOWN(VK_LEFT)) {
            heartsCard.MoveTo(heartsCard.GetX() - 5, heartsCard.GetY());
        }
        if (KEY_DOWN(VK_RIGHT)) {
            heartsCard.MoveTo(heartsCard.GetX() + 5, heartsCard.GetY());
        }
        if (KEY_DOWN(VK_UP)) {
            heartsCard.MoveTo(heartsCard.GetX(), heartsCard.GetY() - 5);
        }
        if (KEY_DOWN(VK_DOWN)) {
            heartsCard.MoveTo(heartsCard.GetX(), heartsCard.GetY() + 5);
        }

        // Перемещение второй карты
        if (KEY_DOWN('A')) {
            clubsCard.MoveTo(clubsCard.GetX() - 5, clubsCard.GetY());
        }
        if (KEY_DOWN('D')) {
            clubsCard.MoveTo(clubsCard.GetX() + 5, clubsCard.GetY());
        }
        if (KEY_DOWN('W')) {
            clubsCard.MoveTo(clubsCard.GetX(), clubsCard.GetY() - 5);
        }
        if (KEY_DOWN('S')) {
            clubsCard.MoveTo(clubsCard.GetX(), clubsCard.GetY() + 5);
        }

        // Проверяем пересечения
        CheckCollisions(&heartsCard, &clubsCard, &shuffler, &dealer);
        
        Sleep(10);
    }
    
    // Освобождаем ресурсы
    DeleteObject(hFont);
    
    return 0;
} 