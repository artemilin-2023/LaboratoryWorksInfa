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

/********************************************************************
 *          ЛАБОРАТОРНАЯ РАБОТА ПО ООП 4 СЕМЕСТР                    *
 *------------------------------------------------------------------*
 * Project Type  : Win64 Console Application                        *
 * Project Name  : Cards                                            *
 * File Name     : main_virt.cpp                                    *
 * Programmer(s) : Ильин Артём М3О-207Б-23                          *
 * Modifyed By   :                                                  *
 * Created       : 08/04/2025                                       *
 * Last Revision : 27/04/2025                                       *
 * Comment(s)    : ИНТЕРФЕЙСЫ И АБСТРАКТНЫЕ БАЗОВЫЕ КЛАССЫ          *
 ********************************************************************/


HDC hdc; // Дескриптор контекста устройства

// Ограничение на количество взаимодействий в секунду
const int INTERACTIONS_PER_SECOND = 2;
const int INTERACTION_INTERVAL = 1000 / INTERACTIONS_PER_SECOND;

// Матрица перехода для взаимодействия карт
const int CARD_TYPES = 2; // Количество типов карт (червы и трефы)
const int INTERACTION_TYPES = 3; // Типы взаимодействий (карта-карта, карта-перемешиватель, карта-раздающий)

// Функция для симуляции взаимодействий
void CollisionSimulation(Card* currentCard,          // Текущая карта
                        ConflictObject** objects,     // Массив объектов взаимодействия
                        Card** cards,                // Массив всех карт
                        int objectCount,              // Количество объектов
                        int cardCount,                // Количество карт
                        int interactionMatrix[][4])   // Матрица взаимодействий
{
    int currentCardIndex = 0; // Индекс текущей карты
    auto lastInteractionTime = steady_clock::now();
    
    while (true) {
        if (KEY_DOWN(VK_ESCAPE)) {
            break;
        }

        // Переключение между картами по пробелу
        if (KEY_DOWN(VK_SPACE)) {
            currentCardIndex = (currentCardIndex + 1) % cardCount;
            currentCard = cards[currentCardIndex];
            Sleep(200); // Задержка для предотвращения множественных переключений
        }

        // Перемещение текущей карты
        if (KEY_DOWN(VK_LEFT)) {
            currentCard->MoveTo(currentCard->GetX() - 5, currentCard->GetY());
        }
        if (KEY_DOWN(VK_RIGHT)) {
            currentCard->MoveTo(currentCard->GetX() + 5, currentCard->GetY());
        }
        if (KEY_DOWN(VK_UP)) {
            currentCard->MoveTo(currentCard->GetX(), currentCard->GetY() - 5);
        }
        if (KEY_DOWN(VK_DOWN)) {
            currentCard->MoveTo(currentCard->GetX(), currentCard->GetY() + 5);
        }

        // Проверяем, прошло ли достаточно времени с последнего взаимодействия
        auto currentTime = steady_clock::now();
        if (duration_cast<milliseconds>(currentTime - lastInteractionTime).count() >= INTERACTION_INTERVAL) {
            // Проверка взаимодействий с другими картами
            for (int i = 0; i < cardCount; i++) {
                if (cards[i] != currentCard && currentCard->IsColliding(dynamic_cast<Point*>(cards[i]))) {
                    int cardType = (currentCard->GetSuit() == "червы") ? 0 : 1;
                    int otherCardType = (cards[i]->GetSuit() == "червы") ? 0 : 1;
                    
                    // Используем матрицу для определения типа взаимодействия
                    int interactionType = interactionMatrix[cardType][otherCardType];
                    
                    switch (interactionType) {
                        case 0: // Нет взаимодействия
                            break;
                        case 1: // Обычное взаимодействие
                            currentCard->Interact(cards[i]);
                            lastInteractionTime = currentTime;
                            break;
                    }
                }
            } 

            // Проверка взаимодействий с объектами
            for (int i = 0; i < objectCount; i++) {
                if (currentCard->IsColliding(objects[i])) {
                    int cardType = (currentCard->GetSuit() == "червы") ? 0 : 1;
                    int objectType = i; // Индекс объекта определяет его тип
                    
                    // Используем матрицу для определения типа взаимодействия
                    int interactionType = interactionMatrix[cardType][objectType + CARD_TYPES];
                    
                    switch (interactionType) {
                        case 0: // Нет взаимодействия
                            break;
                        case 1: // Обычное взаимодействие
                            objects[i]->Interact(currentCard);
                            lastInteractionTime = currentTime;
                            break;
                    }
                }
            }
        }

        Sleep(10);
    }
}

int main()
{
    // Установка кодовой страницы UTF-8 для консоли
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    // Получение дескриптора консольного окна
    HWND hwnd = GetConsoleWindow();

    if (hwnd == NULL) {
        cout << "Дескриптор консольного окна НЕ НАЙДЕН!\n";
        return 1;
    }

    // Получаем контекст устройства для консольного окна
    hdc = GetWindowDC(hwnd);

    if (hdc == 0) {
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
    HeartsCard heartsCard2(500, 200, "Король");
    ClubsCard clubsCard(700, 200, "Король");
    
    // Создаем объекты взаимодействия
    CardShuffler shuffler(400, 400);
    CardDealer dealer(600, 400);
     
    // Массив всех карт
    const int CARD_COUNT = 3;
    Card* cards[CARD_COUNT] = { &heartsCard, &heartsCard2, &clubsCard };
    
    // Массив объектов взаимодействия
    const int OBJECT_COUNT = 2;
    ConflictObject* objects[OBJECT_COUNT] = { &shuffler, &dealer };
    
    // Матрица взаимодействий
    // [0][0] - червы-червы, [0][1] - червы-трефы, [0][2] - червы-перемешиватель, [0][3] - червы-раздающий
    // [1][0] - трефы-червы, [1][1] - трефы-трефы, [1][2] - трефы-перемешиватель, [1][3] - трефы-раздающий
    int interactionMatrix[CARD_TYPES][4] = {
        {0, 1, 1, 1},  // Взаимодействия для червей
        {1, 0, 1, 1}   // Взаимодействия для треф
    };
    
    cout << "Демонстрация работы с картами:\n";
    cout << "1. Используйте стрелки для перемещения карт\n";
    cout << "3. Нажмите пробел для переключения между картами\n";
    cout << "4. При пересечении карт или объектов произойдет взаимодействие\n";
    cout << "5. Нажмите ESC для выхода\n";
    
    // Показываем все объекты
    heartsCard.Show();
    clubsCard.Show();
    shuffler.Show();
    dealer.Show();
    
    // Запускаем симуляцию взаимодействий
    CollisionSimulation(&heartsCard, objects, cards, OBJECT_COUNT, CARD_COUNT, interactionMatrix);
    
    // Освобождаем ресурсы
    DeleteObject(hFont);
    
    return 0;
} 