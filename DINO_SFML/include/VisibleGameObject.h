#pragma once
#include "stdafx.h"

class VisibleGameObject
{
public:
    VisibleGameObject();
    virtual ~VisibleGameObject();

    virtual void Load(std::string filename);
    virtual void Draw(sf::RenderWindow &window);
    virtual void Update(float elapsedTime);
    virtual void SetScale(float x, float y);
    virtual void SetPosition(float x, float y);
    virtual void SetTextureRect(int a, int b, int c, int d);
    virtual void Move(int a, int b);
    virtual sf::Vector2f GetPosition() const;
    virtual sf::FloatRect GetGlobalBounds() const;
    virtual bool IsLoaded() const;

    const sf::Image &GetImage() const;
    sf::Sprite &GetSprite();

protected:
    // sf::Sprite &GetSprite();
    sf::Texture _texture;
    sf::Image _image;

private:
    sf::Sprite _sprite;
    // sf::Texture _texture;
    std::string _filename;
    bool _isLoaded;
};
