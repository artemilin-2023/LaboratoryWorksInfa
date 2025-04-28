#include <iostream>
using namespace std;
#include "card.h"

// Конструктор
Location::Location(int InitX, int InitY)
{
    X = InitX;
    Y = InitY;
}

// Деструктор
Location::~Location()
{
    //Ничего не делает
}

// Получить X
int Location::GetX()
{
    return X;
}

// Получить Y
int Location::GetY()
{
    return Y;
} 