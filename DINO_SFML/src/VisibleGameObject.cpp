#include "../include/stdafx.h"
#include "../include/VisibleGameObject.h"

VisibleGameObject::VisibleGameObject()
    : _isLoaded(false)
{
}

VisibleGameObject::~VisibleGameObject()
{
}

void VisibleGameObject::Load(std::string filename)
{
    if (_texture.loadFromFile(filename) == false)
    {
        _filename = "";
        _isLoaded = false;
    }
    else
    {
        _filename = filename;
        _sprite.setTexture(_texture);
        _image = _texture.copyToImage();
        _isLoaded = true;
    }
}

void VisibleGameObject::Draw(sf::RenderWindow &renderWindow)
{
    if (_isLoaded)
    {
        renderWindow.draw(_sprite);
    }
}

void VisibleGameObject::Update(float elapsedTime)
{
}

void VisibleGameObject::SetScale(float x, float y)
{
    if (_isLoaded)
    {
        _sprite.setScale(x, y);
    }
}
void VisibleGameObject::SetPosition(float x, float y)
{
    if (_isLoaded)
    {
        _sprite.setPosition(x, y);
    }
}
void VisibleGameObject::SetTextureRect(int a, int b, int c, int d)
{
    _sprite.setTextureRect({a, b, c, d});
}
void VisibleGameObject::Move(int a, int b)
{
    _sprite.move(a, b);
}
bool VisibleGameObject::IsLoaded() const
{
    return _isLoaded;
}
sf::Vector2f VisibleGameObject::GetPosition() const
{
    if (_isLoaded)
    {
        return _sprite.getPosition();
    }
    return sf::Vector2f();
}
sf::FloatRect VisibleGameObject::GetGlobalBounds() const
{
    return _sprite.getGlobalBounds();
}
sf::Sprite &VisibleGameObject::GetSprite()
{
    return _sprite;
}
const sf::Image &VisibleGameObject::GetImage() const
{
    return _image;
}
