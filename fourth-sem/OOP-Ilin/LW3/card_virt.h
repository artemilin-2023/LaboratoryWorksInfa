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
    virtual void Show() = 0;
    virtual void Hide() = 0;
    virtual void MoveTo(int NewX, int NewY) = 0;
    virtual void Flip() = 0;
    virtual void Interact(ICard* other) = 0;
    virtual string GetRank() = 0;
    virtual string GetSuit() = 0;
    virtual bool GetIsFaceUp() = 0;
    virtual void SetIsFaceUp(bool value) = 0;
    virtual bool IsColliding(Point* other) = 0;
    virtual int GetX() = 0;
    virtual int GetY() = 0;
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
public:
    Card(int InitX, int InitY, string InitRank, string InitSuit, int InitWidth, int InitHeight);
    virtual ~Card();
    
    // Реализация методов интерфейса ICard
    string GetRank() override { return Rank; }
    string GetSuit() override { return Suit; }
    bool GetIsFaceUp() override { return IsFaceUp; }
    void SetIsFaceUp(bool value) override { IsFaceUp = value; }
    int GetX() override { return X; }
    int GetY() override { return Y; }
    
    // Виртуальные методы
    virtual void Show() override;
    virtual void Hide() override;
    virtual void MoveTo(int NewX, int NewY) override;
    virtual void ChangeHitbox() override;
    virtual void Flip() override;  // Перевернуть карту
    virtual void Interact(ICard* other) override;  // Взаимодействие с другой картой
    bool IsColliding(Point* other) override { return Point::IsColliding(other); }
};

// Класс карты червей
class HeartsCard : public Card {
public:
    HeartsCard(int InitX, int InitY, string InitRank);
    ~HeartsCard() override;
    
    void Show() override;
    void Interact(ICard* other) override;
};

// Класс карты треф
class ClubsCard : public Card {
public:
    ClubsCard(int InitX, int InitY, string InitRank);
    ~ClubsCard() override;
    
    void Show() override;
    void Interact(ICard* other) override;
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
