#pragma once
#include "VisibleGameObject.h"
#include "Dinosaur.h"

class Cactus : public VisibleGameObject
{
public:
    Cactus();
    void Create();
    void Move();
    bool Collide(Dinosaur &dinosaur);
    double *GetSpeed();

private:
    double speed;
};
