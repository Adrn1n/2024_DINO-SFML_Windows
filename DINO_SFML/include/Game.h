#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "VisibleGameObject.h"

class Game
{
public:
    static void Start();
    static sf::RenderWindow &GetWindow();
    static sf::View &GetView();
    const static sf::Event &GetInput();

    const static int SCREEN_WIDTH = 1280;
    const static int SCREEN_HEIGHT = 720;

private:
    static bool IsExiting();
    static void GameLoop();
    static void ShowSplashScreen();
    static void ShowMenu();
    static void ShowSettingScreen();
    static void ShowHelp();
    static void ShowPause();

    enum GameState
    {
        Uninitialized,
        ShowingSplash,
        Paused,
        ShowingMenu,
        ShowingSetting,
        ShowPauseScreen,
        Playing,
        Restart,
        Dead,
        Exiting,
        Helping,
        Load
    };

    static GameState _gameState;
    static sf::View view;
    static sf::RenderWindow _mainWindow;
    sf::Clock *cl;
};
