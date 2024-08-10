#pragma once
#include "VisibleGameObject.h"

class Cloud : public VisibleGameObject
{
public:
    Cloud();
    void Create(int n);
    void Move();
    double *GetSpeed();

private:
    double speed;
};
