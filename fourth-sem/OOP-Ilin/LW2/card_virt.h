#pragma once
#include <iostream>
#include <string>
#include <windows.h>
using std::cout;
using std::endl;
using std::string;

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
    ~Point();

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
class Card : public Point {
protected:
    string Rank;    // Достоинство карты (Туз, Король, Дама и т.д.)
    string Suit;    // Масть карты (пики, червы, бубны, трефы)
    int Width;
    int Height;
    bool IsFaceUp;  // Карта рубашкой вверх или вниз
public:
    Card(int InitX, int InitY, string InitRank, string InitSuit, int InitWidth, int InitHeight);
    virtual ~Card();
    
    // Геттеры
    string GetRank() { return Rank; }
    string GetSuit() { return Suit; }
    int GetWidth() { return Width; }
    int GetHeight() { return Height; }
    bool GetIsFaceUp() { return IsFaceUp; }
    
    // Сеттеры
    void SetIsFaceUp(bool value) { IsFaceUp = value; }
    
    // Виртуальные методы
    virtual void Show() override;
    virtual void Hide() override;
    virtual void MoveTo(int NewX, int NewY) override;
    virtual void ChangeHitbox() override;
    virtual void Flip();  // Перевернуть карту
    virtual void Interact(Card* other);  // Взаимодействие с другой картой
};

// Класс карты червей
class HeartsCard : public Card {
public:
    HeartsCard(int InitX, int InitY, string InitRank);
    ~HeartsCard() override;
    
    void Show() override;
    void Interact(Card* other) override;
};

// Класс карты треф
class ClubsCard : public Card {
public:
    ClubsCard(int InitX, int InitY, string InitRank);
    ~ClubsCard() override;
    
    void Show() override;
    void Interact(Card* other) override;
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
    virtual void Interact(Card* card) = 0;  // Взаимодействие с картой
};

// Класс перемешивателя карт
class CardShuffler : public ConflictObject {
public:
    CardShuffler(int InitX, int InitY);
    ~CardShuffler() override;
    
    void Show() override;
    void Interact(Card* card) override;
};

// Класс раздающего карты
class CardDealer : public ConflictObject {
public:
    CardDealer(int InitX, int InitY);
    ~CardDealer() override;
    
    void Show() override;
    void Interact(Card* card) override;
}; 
