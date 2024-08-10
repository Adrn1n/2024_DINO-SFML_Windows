#include "../include/Background.h"

Background::Background() : speed(10)
{
}

void Background::Move()
{
    GetSprite().move(-speed, 0);
    speed += 0.001;
    while (this->GetPosition().x <= -5920)
        this->SetPosition(0, 340);
}
double *Background::GetSpeed()
{
    double *x = &speed;
    return x;
}
