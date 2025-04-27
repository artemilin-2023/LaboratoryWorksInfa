#pragma once
#include <iostream>
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