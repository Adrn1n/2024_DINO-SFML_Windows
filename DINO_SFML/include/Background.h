#pragma once
#include "VisibleGameObject.h"

class Background : public VisibleGameObject
{
public:
    Background();
    void Move();
    double *GetSpeed();

private:
    double speed;
};
