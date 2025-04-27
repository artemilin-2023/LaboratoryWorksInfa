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
    
    virtual void Drag(int Step);
    virtual void Show();
    virtual void Hide();
    virtual void MoveTo(int NewX, int NewY);
}; 