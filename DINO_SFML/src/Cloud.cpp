#include "../include/Cloud.h"

Cloud::Cloud() : speed(10)
{
}
void Cloud::Create(int n)
{

    srand(n);
    int random = rand() % 4;
    this->SetPosition(1200 + 5 * random, 15 * (4 - random));
}

void Cloud::Move()
{
    GetSprite().move(-speed, 0);
    speed += 0.001;
}
double *Cloud::GetSpeed()
{
    double *x = &speed;
    return x;
}
