#pragma once
#include "VisibleGameObject.h"
#include "Dinosaur.h"

class Bird : public VisibleGameObject
{
public:
    Bird();
    void Create();
    void Fly();
    void Move();
    bool Collide(Dinosaur &dinosaur);
    double *GetSpeed();

private:
    double speed;
    int frame;
};
