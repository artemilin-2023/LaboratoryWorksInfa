#include <iostream>
using std::cout;
using std::endl;
#include "card_virt.h"

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

// Установить X
void Location::SetX(int NewX)
{
    X = NewX;
}

// Установить Y
void Location::SetY(int NewY)
{
    Y = NewY;
} 