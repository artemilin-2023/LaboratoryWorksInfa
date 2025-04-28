#pragma once
#include <iostream>
#include <string>
using namespace std;

class Location {
protected:
    int X, Y;
public:
    Location(int InitX, int InitY);
    ~Location();
    int GetX();
    int GetY();
    void SetX(int NewX) { X = NewX; };
    void SetY(int NewY) { Y = NewY; };
};

class Point : public Location {
protected:
    bool Visible;
public:
    Point(int InitX, int InitY);
    ~Point();
    
    bool GetVisible();
    void SetVisible(bool NewVisible);
    
    void Drag(int Step);
    void Show();
    void Hide();
    void MoveTo(int NewX, int NewY);
}; 

// Класс карты, наследующийся от Point
class Card : public Point {
private:
    string Rank;    // Достоинство карты (Туз, Король, Дама и т.д.)
    string Suit;    // Масть карты (пики, червы, бубны, трефы)
    int Width, Height;
public:
    Card(int InitX=200, int InitY=200, string InitRank="Туз", string InitSuit="пики", 
         int InitWidth=100, int InitHeight=150);
    ~Card();
    
    // Геттеры
    string GetRank() { return Rank; }
    string GetSuit() { return Suit; }
    int GetWidth() { return Width; }
    int GetHeight() { return Height; }
    
    // Переопределение методов из Point
    void Show();
    void Hide();
    void MoveTo(int NewX, int NewY);
    void Drag(int Step);
}; 