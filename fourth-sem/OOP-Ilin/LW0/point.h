#pragma once
#include <iostream>
using namespace std;
#include "location.h"

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