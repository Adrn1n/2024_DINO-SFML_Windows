#include "../include/Dinosaur.h"

Dinosaur::Dinosaur() : speed_x(150), speed_y(0), frame(0), jumping_clock(nullptr)
{
    jumping_t.Zero;
}
void Dinosaur::Run()
{

    if (frame <= 10)
    {
        this->SetTextureRect(88, 0, 44, 47);
        frame++;
    }
    else if (frame <= 20)
    {
        this->SetTextureRect(132, 0, 44, 47);
        frame++;
    }
    else
        frame = 0;
}
void Dinosaur::Jump()
{
    if (this->GetPosition().y > 10)
        this->Move(0, -speed_y);
}
void Dinosaur::Fall()
{
    if (this->GetPosition().y <= 230)
        this->Move(0, speed_y);
}
void Dinosaur::Over()
{
    this->SetTextureRect(176, 0, 44, 47);
}

int Dinosaur::Set_y_v(int val)
{
    speed_y = val;
    return speed_y;
}

int Dinosaur::Get_y_v()
{
    return speed_y;
}
