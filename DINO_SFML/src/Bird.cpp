#include "../include/Bird.h"
#include "../include/Cactus.h"

Bird::Bird() : speed(10), frame(0)
{
}
void Bird::Create()
{
    this->SetTextureRect(0, 0, 90, 80);
    srand(time(NULL));
    int random = rand() % 2;
    this->SetPosition(1200, 100 * random);
}
void Bird::Fly()
{
    if (frame <= 10)
    {
        this->SetTextureRect(0, 0, 90, 80);
        frame++;
    }
    else if (frame <= 20)
    {
        this->SetTextureRect(90, 0, 90, 80);
        frame++;
    }
    else
        frame = 0;
}
void Bird::Move()
{
    GetSprite().move(-speed, 0);
    speed += 0.001;
}
bool Bird::Collide(Dinosaur &dinosaur)
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

double *Bird::GetSpeed()
{
    double *x = &speed;
    return x;
}
