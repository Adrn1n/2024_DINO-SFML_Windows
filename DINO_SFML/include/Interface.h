#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Settings.h"
#include <list>

sf::Vector2f changeV2itoV2f(sf::Vector2i vec);
sf::Vector2i changeV2ftoV2i(sf::Vector2f vec);
sf::Vector2i getMousePosition(sf::RenderWindow &window);

template <typename T>
void setOriginToLeft(T &drawable)
{
    sf::FloatRect bounds = drawable.getLocalBounds();
    drawable.setOrigin(bounds.left, bounds.top + bounds.height / 2.0f);
}

template <typename T>
void setOriginToRight(T &drawable)
{
    sf::FloatRect bounds = drawable.getLocalBounds();
    drawable.setOrigin(bounds.left + bounds.width, bounds.top + bounds.height / 2.0f);
}

template <typename T>
void setOriginToCenter(T &drawable)
{
    sf::FloatRect bounds = drawable.getLocalBounds();
    drawable.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}

class Button
{
public:
    Button(const sf::View &view, float x, float y, float width, float height, const std::string &text);
    void draw(sf::RenderWindow &window, const sf::View &view);
    bool isClicked(sf::Vector2i mousePos);
    bool isPutOn(sf::Vector2i mousePos);
    static std::string getClickButtonName(sf::Vector2i clickPosition, std::list<Button> &Buttons);

private:
    sf::RectangleShape shape;
    sf::Text buttonText;
    sf::Font font;
    sf::View originalView;
    sf::Vector2f originalPosition;
    sf::Vector2f originalSize;
    sf::Color originalColor;

    bool wasPutOn;
    void updateAppearance(sf::RenderWindow &window, const sf::View &view);
};

class Slider
{
public:
    Slider(const std::string &name, float width, float height, float current_value, float max_value = 100.0);
    void setPosition(const sf::View &view, float x, float y);
    void follow(sf::RenderWindow &window);
    float getValue() const;
    void setValue(float current_value);
    void draw(sf::RenderWindow &window, sf::Event &event);
    sf::FloatRect getGlobalBounds() const;
    void detectPressMouse(sf::RenderWindow &window);

private:
    void updateSlider(float length);
    std::string _name;
    float _width, _height;
    float _max_value, _current_value;

    bool isSliderDragged;
    bool wasButtonClicked;
    bool isButtonClicked;

    sf::Color _ButtonColor;
    sf::RectangleShape _background;
    sf::RectangleShape _current_slider;
    sf::RectangleShape _button;
    sf::Text _nameText;
    sf::Font _font;
    const float _thickness = 3.0f;
};
