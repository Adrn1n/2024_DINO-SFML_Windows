#pragma once
#include "VisibleGameObject.h"

class Dinosaur : public VisibleGameObject
{
public:
    Dinosaur();

    void Run();
    void Jump();
    void Fall();
    void Over();
    int Set_y_v(int val);
    int Get_y_v();

private:
    int speed_x;
    int speed_y;
    int frame;
    sf::Clock *jumping_clock;
    sf::Time jumping_t;
};
