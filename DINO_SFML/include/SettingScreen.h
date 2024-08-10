#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "Interface.h"
#include <map>
#include <string>

class SettingScreen
{
public:
    void updateSetItem(sf::RenderWindow &window, sf::View &view, sf::Event &event);
    enum SetResult
    {
        Nothing,
        Exit,
        Help,
        Menu
    };
    SetResult Show(sf::RenderWindow &window);

private:
    static sf::Texture backgroundTexture;
    static sf::Sprite backgroundSprite;
    static std::list<Slider *> Sliders;
    static std::list<Button> Buttons;
};
