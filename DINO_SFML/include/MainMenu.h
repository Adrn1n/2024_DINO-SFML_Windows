#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Interface.h"
#include "Game.h"
#include <list>

class MainMenu
{

public:
    static void DrawMenu(sf::RenderWindow &window, sf::View &view);
    static void DrawDifficulty(sf::RenderWindow &window, sf::View &view);
    enum MenuResult
    {
        Nothing,
        Exit,
        Easy,
        Normal,
        Hard,
        Setting,
        Play,
        Loading
    };
    enum MenuState
    {
        MAIN_MENU1,
        MAIN_MENU2,
        DIFFICULTY_SELECTION
    };
    MenuResult Show(sf::RenderWindow &window);

private:
    static MenuState menuState;
    static sf::Texture backgroundTexture;
    static sf::Sprite backgroundSprite;
    static sf::Texture DifficultyTexture;
    static sf::Sprite DifficultySprite;
    static std::list<Button> Buttons;
    static std::list<Button> DifficultyButtons;
};
