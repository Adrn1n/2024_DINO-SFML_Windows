#include "../include/Cactus.h"

Cactus::Cactus() : speed(10)
{
}
void Cactus::Create()
{
    srand(time(NULL));
    this->SetPosition(1200, 250);
    int random = rand() % 5;
    switch (random)
    {
    case 0:
        this->SetTextureRect(0, 0, 25, 53);
        break;
    case 1:
        this->SetTextureRect(25, 0, 25, 53);
        break;
    case 2:
        this->SetTextureRect(50, 0, 25, 53);
        break;
    case 3:
        this->SetTextureRect(75, 0, 25, 53);
        break;
    case 4:
        this->SetTextureRect(100, 0, 28, 53);
        break;
    }
}
void Cactus::Move()
{
    GetSprite().move(-speed, 0);
    speed += 0.001;
}
bool Cactus::Collide(Dinosaur &dinosaur)
{

    sf::Rect<float> dino = dinosaur.GetGlobalBounds();
    sf::Rect<float> cac = this->GetGlobalBounds();
    if (cac.intersects(dino))
    {
        dinosaur.Over();
        return true;
    }
    else
        return false;
}
double *Cactus::GetSpeed()
{
    double *x = &speed;
    return x;
}
