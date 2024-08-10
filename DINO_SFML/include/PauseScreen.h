#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Interface.h"
#include "Game.h"
#include <list>

class PauseScreen
{

public:
    static void DrawPause(sf::RenderWindow &window, sf::View &view);
    enum PauseResult
    {
        Resume,
        Restart,
        Save,
        Set,
        Exit
    };
    PauseResult Show(sf::RenderWindow &window);

private:
    static sf::Texture backgroundTexture;
    static sf::Sprite backgroundSprite;
    static std::list<Button> Buttons;
};
