#pragma once
#include <iostream>
#include <string>
#include <windows.h>
using std::cout;
using std::endl;
using std::string;

// Предварительное объявление класса Point
class Point;

// Интерфейс для карт
class ICard {
public:
    virtual ~ICard() = default;
    virtual void DrawRank() = 0;  // Отрисовка достоинства карты
    virtual void DrawSuit() = 0;  // Отрисовка масти карты
    virtual void DrawBack() = 0;  // Отрисовка рубашки карты
    virtual void DrawCenterSuit() = 0;  // Отрисовка центральной масти
    virtual void MoveTo(int NewX, int NewY) = 0;
    virtual void Flip() = 0;
    virtual void Interact(ICard* other) = 0;
    virtual string GetRank() = 0;
    virtual string GetSuit() = 0;
    virtual bool GetIsFaceUp() = 0;
    virtual void SetIsFaceUp(bool value) = 0;
    virtual bool IsColliding(Point* other) = 0;
    // virtual int GetX() = 0;
    // virtual int GetY() = 0;
    virtual void Show() = 0;  // Добавляем Show в интерфейс
};

class Location {
protected:
    int X;
    int Y;
public:
    Location(int InitX, int InitY);
    ~Location();
    int GetX();
    int GetY();
    void SetX(int NewX);
    void SetY(int NewY);
}; 

class Point : public Location {
protected:
    bool Visible;
    int rightBorder;
    int leftBorder;
    int topBorder;
    int bottomBorder;

public:
    Point(int InitX, int InitY);
    virtual ~Point();

    bool IsVisible();
    bool GetVisible();
    void SetVisible(bool NewVisible);
    int GetRightBorder();
    int GetLeftBorder();
    int GetTopBorder();
    int GetBottomBorder();

    virtual void MoveTo(int NewX, int NewY);
    void Drag(int Step);
    virtual void Show();
    virtual void Hide();
    virtual void ChangeHitbox();
    bool IsColliding(Point* other);
};

// Базовый класс для карт
class Card : public Point, public ICard {
protected:
    string Rank;    // Достоинство карты (Туз, Король, Дама и т.д.)
    string Suit;    // Масть карты (пики, червы, бубны, трефы)
    int Width;
    int Height;
    bool IsFaceUp;  // Карта рубашкой вверх или вниз

    // Вспомогательные методы для отрисовки
    void DrawCardBorder();  // Отрисовка границы карты
    void DrawCardBackground();  // Отрисовка фона карты

public:
    Card(int InitX, int InitY, string InitRank, string InitSuit, int InitWidth, int InitHeight);
    virtual ~Card();
    
    // Реализация методов интерфейса ICard
    string GetRank() override { return Rank; }
    string GetSuit() override { return Suit; }
    bool GetIsFaceUp() override { return IsFaceUp; }
    void SetIsFaceUp(bool value) override { IsFaceUp = value; }
    // int GetX() override { return X; }
    // int GetY() override { return Y; }
    
    // Виртуальные методы отрисовки
    virtual void DrawRank() override;  // Базовая реализация отрисовки ранга
    virtual void DrawSuit() override;  // Базовая реализация отрисовки масти
    virtual void DrawBack() override;  // Базовая реализация отрисовки рубашки
    virtual void DrawCenterSuit() override;  // Базовая реализация отрисовки центральной масти
    virtual void Show() override;      // Общая реализация отрисовки карты
    
    // Остальные виртуальные методы
    virtual void Hide() override;
    virtual void MoveTo(int NewX, int NewY) override;
    virtual void ChangeHitbox() override;
    virtual void Flip() override;
    virtual void Interact(ICard* other) override;
    bool IsColliding(Point* other) override { return Point::IsColliding(other); }
};

// Класс карты червей
class HeartsCard : public Card {
public:
    HeartsCard(int InitX, int InitY, string InitRank);
    ~HeartsCard() override;
    
    void DrawRank() override;  // Специфичная реализация для червей
    void DrawSuit() override;  // Специфичная реализация для червей
    void DrawCenterSuit() override;  // Специфичная реализация для червей
};

// Класс карты треф
class ClubsCard : public Card {
public:
    ClubsCard(int InitX, int InitY, string InitRank);
    ~ClubsCard() override;
    
    void DrawRank() override;  // Специфичная реализация для треф
    void DrawSuit() override;  // Специфичная реализация для треф
    void DrawCenterSuit() override;  // Специфичная реализация для треф
};

// Базовый класс для объектов взаимодействия
class ConflictObject : public Point {
protected:
    int Width;
    int Height;
public:
    ConflictObject(int InitX, int InitY, int InitWidth, int InitHeight);
    virtual ~ConflictObject();
    
    virtual void Show() override;
    virtual void Hide() override;
    virtual void ChangeHitbox() override;
    virtual void Interact(ICard* card) = 0;  // Взаимодействие с картой
};

// Класс перемешивателя карт
class CardShuffler : public ConflictObject {
public:
    CardShuffler(int InitX, int InitY);
    ~CardShuffler() override;
    
    void Show() override;
    void Interact(ICard* card) override;
};

// Класс раздающего карты
class CardDealer : public ConflictObject {
public:
    CardDealer(int InitX, int InitY);
    ~CardDealer() override;
    
    void Show() override;
    void Interact(ICard* card) override;
}; 
