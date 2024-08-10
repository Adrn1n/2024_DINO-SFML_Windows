#include "../include/stdafx.h"
#include "../include/Game.h"

#include "../include/MainMenu.h"
#include "../include/SplashScreen.h"
#include "../include/SFMLSoundProvider.h"
#include "../include/ServiceLocator.h"
#include "../include/SettingScreen.h"
#include "../include/Help.h"
#include "../include/PauseScreen.h"

#include "../include/Dinosaur.h"
#include "../include/Cactus.h"
#include "../include/Bird.h"
#include "../include/Cloud.h"
#include "../include/Background.h"

#include <iostream>
#include <fstream>

#include <SFML/Audio.hpp>

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
VisibleGameObject end, restart;
Background background;
Dinosaur dinosaur;
Cactus cactus;
sf::View Game::view;

Bird bird;
Cloud cloud1, cloud2, cloud3;

int flag = 1;

bool if_pix_intersects(const sf::Sprite &sprite1, const sf::Image &image1, const sf::Sprite &sprite2, const sf::Image &image2)
{
    sf::FloatRect intersection;
    if (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds(), intersection))
    {
        sf::IntRect subRect1 = sprite1.getTextureRect();
        sf::IntRect subRect2 = sprite2.getTextureRect();

        for (int i = intersection.left; i < intersection.left + intersection.width; i++)
        {
            for (int j = intersection.top; j < intersection.top + intersection.height; j++)
            {
                sf::Vector2f p1 = sprite1.getInverseTransform().transformPoint(i, j);
                sf::Vector2f p2 = sprite2.getInverseTransform().transformPoint(i, j);

                if (p1.x > 0 && p1.y > 0 && p1.x < subRect1.width && p1.y < subRect1.height &&
                    p2.x > 0 && p2.y > 0 && p2.x < subRect2.width && p2.y < subRect2.height)
                {
                    if (image1.getPixel(p1.x, p1.y).a != 0 && image2.getPixel(p2.x, p2.y).a != 0)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

double backgroundspeed, dinox, dinoy, backgroundx, backgroundy, cactusx, cactusy, cloud1x, cloud1y, cloud2x, cloud2y, cloud3x, cloud3y, birdx, birdy;
void Game::Start(void)
{
    if (_gameState != Uninitialized)
        return;
    _mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Dinosaur!");
    _mainWindow.setFramerateLimit(60);
    view = _mainWindow.getView();
    SFMLSoundProvider soundProvider;
    ServiceLocator::RegisterServiceLocator(&soundProvider);

    // soundProvider.PlaySong("./assets/audio/01.Unwelcome School.mp3",true);

    dinosaur.Load("./assets/image/dinosaur.png");
    dinosaur.SetScale(3, 3);
    dinosaur.SetPosition(50, 230);
    cactus.Load("./assets/image/cactus.png");
    cactus.SetScale(2, 2);
    cactus.SetPosition(-50, 250);
    bird.Load("./assets/image/bird.png");
    bird.SetScale(1, 1);
    bird.SetPosition(-50, 200);
    cloud1.Load("./assets/image/clouds.png");
    cloud2.Load("./assets/image/clouds.png");
    cloud3.Load("./assets/image/clouds.png");
    cloud1.SetScale(2, 2);
    cloud2.SetScale(2, 2);
    cloud3.SetScale(2, 2);
    background.Load("./assets/image/GroundImage.png");
    background.SetScale(3, 3);
    background.SetPosition(0, 340);
    end.Load("./assets/image/gameover.png");
    end.SetScale(3, 3);
    end.SetPosition(315, 150);
    restart.Load("./assets/image/restart.png");
    restart.SetScale(3, 3);
    restart.SetPosition(546, 220);

    _gameState = Game::ShowingSplash; // 初始化窗口以及游戏素材

    while (!IsExiting())
    {
        GameLoop();
    }

    _mainWindow.close();
}

bool Game::IsExiting()
{
    if (_gameState == Game::Exiting)
        return true;
    else
        return false;
}

sf::RenderWindow &Game::GetWindow()
{
    return _mainWindow;
}

sf::View &Game::GetView()
{
    return view;
}

const sf::Event &Game::GetInput()
{
    static sf::Event currentEvent;
    _mainWindow.pollEvent(currentEvent);
    return currentEvent;
}

void Game::GameLoop()
{
    sf::Event currentEvent;
    _mainWindow.pollEvent(currentEvent);

    switch (_gameState)
    {
    case Game::ShowingSplash:
    {
        ShowSplashScreen();
        _mainWindow.clear();
        break;
    }
    case Game::ShowingMenu:
    {
        ShowMenu();
        break;
    }
    case Game::ShowingSetting:
    {
        ShowSettingScreen();
        break;
    }
    case Game::ShowPauseScreen:
    {

        ShowPause();
        break;
    }
    case Game::Helping:
    {
        ShowHelp();
        break;
    }
    case Game::Load:
    {

        ServiceLocator::GetAudio()->PlaySong("./assets/audio/Game.ogg", true, Settings::getSongVolume());
        _mainWindow.clear(sf::Color::White);
        background.SetTextureRect(0, 0, 2400, 20);
        background.Draw(_mainWindow);
        // dinosaur.SetPosition(dinox, dinoy);
        cactus.SetTextureRect(0, 0, 25, 53);
        cactus.SetPosition(cactusx, cactusy);
        bird.SetPosition(birdx, birdy);
        bird.SetTextureRect(0, 0, 90, 80);
        cloud1.SetPosition(cloud1x, cloud1y);
        cloud2.SetPosition(cloud2x, cloud2y);
        cloud3.SetPosition(cloud3x, cloud3y);
        dinosaur.SetTextureRect(0, 0, 44, 47);
        dinosaur.Draw(_mainWindow);
        bird.Draw(_mainWindow);
        cactus.Draw(_mainWindow);
        cloud1.Draw(_mainWindow);
        cloud2.Draw(_mainWindow);
        cloud3.Draw(_mainWindow);
        _mainWindow.display(); // 未开始游戏时窗口的绘制
        // 绘制恐龙和背景
        if (currentEvent.key.code == sf::Keyboard::Space)
        {
            *background.GetSpeed() = backgroundspeed;
            *cactus.GetSpeed() = backgroundspeed;
            *bird.GetSpeed() = backgroundspeed;
            *cloud1.GetSpeed() = backgroundspeed;
            *cloud2.GetSpeed() = backgroundspeed;
            *cloud3.GetSpeed() = backgroundspeed;
            _gameState = Game::Playing;
        }

        if (currentEvent.key.code == sf::Keyboard::Escape)
        {
            _gameState = Game::ShowPauseScreen;
        }

        break;
    }
    case Game::Paused:
    {

        ServiceLocator::GetAudio()->PlaySong("./assets/audio/Game.ogg", true, Settings::getSongVolume());
        _mainWindow.clear(sf::Color::White);
        background.SetTextureRect(0, 0, 2400, 20);
        background.Draw(_mainWindow);
        dinosaur.SetPosition(50, 230);
        cactus.SetTextureRect(0, 0, 25, 53);
        cactus.SetPosition(-100, 250);
        bird.SetPosition(1600, 230);
        cloud1.SetPosition(1600, 0);
        cloud2.SetPosition(600, 60);
        cloud3.SetPosition(1000, 30);
        dinosaur.SetTextureRect(0, 0, 44, 47);
        dinosaur.Draw(_mainWindow);
        cloud1.Draw(_mainWindow);
        cloud2.Draw(_mainWindow);
        cloud3.Draw(_mainWindow);
        _mainWindow.display(); // 未开始游戏时窗口的绘制
                               // 绘制恐龙和背景
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            _gameState = Game::Playing;
        }
        // if (currentEvent.key.code == sf::Keyboard::Space)
        // {
        // 	_gameState = Game::Playing;
        // }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            _gameState = Game::ShowPauseScreen;
        }

        // if (currentEvent.key.code == sf::Keyboard::Escape)
        // {
        // 	_gameState = Game::ShowPauseScreen;
        // }

        break;
    }

    case Game::Playing:
    {

        _mainWindow.clear(sf::Color::White);
        background.Move();
        background.Draw(_mainWindow);
        dinosaur.Draw(_mainWindow);
        if (cactus.GetPosition().x <= -50 && bird.GetPosition().x <= 900) // creating a new cactus
        {
            cactus.Create();
        }
        srand(time(NULL));
        int random = rand() % 5;
        if (bird.GetPosition().x <= -100 * random && cactus.GetPosition().x <= 900) // creating a new bird
        {
            bird.Create();
        }
        if (cloud1.GetPosition().x <= -95)
        {
            cloud1.Create(random + 3);
        }
        if (cloud2.GetPosition().x <= -95)
        {
            cloud2.Create(random);
        }
        if (cloud3.GetPosition().x <= -95)
        {
            cloud3.Create(random + 1);
        }

        cactus.Move();
        bird.Move();
        bird.Fly();
        cloud1.Move();
        cloud2.Move();
        cloud3.Move();
        cactus.Draw(_mainWindow);
        bird.Draw(_mainWindow);
        cloud1.Draw(_mainWindow);
        cloud2.Draw(_mainWindow);
        cloud3.Draw(_mainWindow);
        _mainWindow.display();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            dinosaur.Jump();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            dinosaur.Fall();
        }
        // if (currentEvent.key.code == sf::Keyboard::Space)
        // {
        // 	dinosaur.Jump();
        // }
        else
            dinosaur.Run();
        auto cactus_bd = cactus.GetGlobalBounds(), bird_bd = bird.GetGlobalBounds(), dino_bd = dinosaur.GetGlobalBounds();
        // if (cactus.Collide(dinosaur) || bird.Collide(dinosaur))
        if (if_pix_intersects(dinosaur.GetSprite(), dinosaur.GetImage(), cactus.GetSprite(), cactus.GetImage()) ||
            if_pix_intersects(dinosaur.GetSprite(), dinosaur.GetImage(), bird.GetSprite(), bird.GetImage()))
        {
            ServiceLocator::GetAudio()->StopSong();
            _gameState = Game::Restart;
        }

        if (currentEvent.key.code == sf::Keyboard::Escape)
        {
            _gameState = Game::ShowPauseScreen;
        }

        break;
    }
    case Game::Restart:
    {
        _mainWindow.clear(sf::Color::White);
        background.Draw(_mainWindow);
        dinosaur.Draw(_mainWindow);
        cactus.Draw(_mainWindow);
        end.Draw(_mainWindow);
        restart.Draw(_mainWindow); // 碰撞到仙人掌，重开游戏时窗口的绘制
        _mainWindow.display();
        // if (currentEvent.key.code == sf::Keyboard::Space)
        // {
        // 	_gameState = Game::Paused;
        // }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            _gameState = Game::Paused;
        }
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        // {
        // 	_gameState = Game::ShowPauseScreen;
        // }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            _gameState = Game::ShowPauseScreen;
        }

        break;
    }
    }
    if (currentEvent.type == sf::Event::Closed)
    {
        _gameState = Game::Exiting;
    }
}

void Game::ShowSplashScreen()
{
    SplashScreen splashScreen;
    splashScreen.Show(_mainWindow);
    _gameState = Game::ShowingMenu;
}

void Game::ShowSettingScreen()
{
    SettingScreen settingScreen;
    SettingScreen::SetResult result = settingScreen.Show(_mainWindow);
    switch (result)
    {
    case (SettingScreen::Menu):
        _gameState = ShowingMenu;
        break;
    case (SettingScreen::Exit):
        _gameState = Exiting;
        break;
    case (SettingScreen::Help):
        _gameState = Helping;
        break;
    }
}

void Game::ShowHelp()
{
    Help help;
    help.Show(_mainWindow);
    Help::HelpResult result = help.Show(_mainWindow);
    switch (result)
    {
    case Help::Setting:
        _gameState = ShowingSetting;
        break;
    case Help::Exit:
    {
        _gameState = Exiting;
        break;
    }
    }
}
void Game::ShowMenu()
{
    MainMenu mainMenu;
    MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
    switch (result)
    {
    case MainMenu::Loading:
    {
        std::ifstream is;
        is.open("./save.txt", std::ios::in);

        int tmp_dino_v_y = 0;

        is >> backgroundspeed >> dinox >> dinoy >> backgroundx >> backgroundy >> cactusx >> cactusy >> cloud1x >> cloud1y >> cloud2x >> cloud2y >> cloud3x >> cloud3y >> birdx >> birdy >> tmp_dino_v_y;
        dinosaur.Set_y_v(tmp_dino_v_y);
        is.close();
        _gameState = Load;
        break;
    }
    case MainMenu::Exit:
        _gameState = Exiting;
        break;
    case MainMenu::Play:
    {
        ServiceLocator::GetAudio()->StopSong();

        _gameState = Paused;
        break;
    }
    case MainMenu::Setting:
    {
        ServiceLocator::GetAudio()->StopSong();
        _gameState = ShowingSetting;
        break;
    }
    case MainMenu::Easy:
    {
        _gameState = Paused;
        *background.GetSpeed() = 15;
        *cactus.GetSpeed() = 15;
        *bird.GetSpeed() = 15;
        *cloud1.GetSpeed() = 15;
        *cloud2.GetSpeed() = 15;
        *cloud3.GetSpeed() = 15;
        dinosaur.Set_y_v(25);
        break;
    }
    case MainMenu::Normal:
    {
        _gameState = Paused;
        *background.GetSpeed() = 20;
        *cactus.GetSpeed() = 20;
        *bird.GetSpeed() = 20;
        *cloud1.GetSpeed() = 20;
        *cloud2.GetSpeed() = 20;
        *cloud3.GetSpeed() = 20;
        dinosaur.Set_y_v(50);
        break;
    }
    case MainMenu::Hard:
    {
        _gameState = Paused;
        *background.GetSpeed() = 25;
        *cactus.GetSpeed() = 25;
        *bird.GetSpeed() = 25;
        *cloud1.GetSpeed() = 25;
        *cloud2.GetSpeed() = 25;
        *cloud3.GetSpeed() = 25;
        dinosaur.Set_y_v(25);
        break;
    }
    }
}

void Game::ShowPause()
{
    double tempspeed = *cactus.GetSpeed();
    *background.GetSpeed() = 0;
    *cactus.GetSpeed() = 0;
    *bird.GetSpeed() = 0;
    *cloud1.GetSpeed() = 0;
    *cloud2.GetSpeed() = 0;
    *cloud3.GetSpeed() = 0;
    PauseScreen pause;
    PauseScreen::PauseResult result = pause.Show(_mainWindow);
    switch (result)
    {
    case (PauseScreen::Resume):
    {
        *background.GetSpeed() = tempspeed;
        *cactus.GetSpeed() = tempspeed;
        *bird.GetSpeed() = tempspeed;
        *cloud1.GetSpeed() = tempspeed;
        *cloud2.GetSpeed() = tempspeed;
        *cloud3.GetSpeed() = tempspeed;
        ServiceLocator::GetAudio()->ResumeSong();
        // _gameState = Playing;
        if (flag == 1)
            _gameState = Playing;
        else
            _gameState = Restart;

        break;
    }
    case (PauseScreen::Restart):
    {

        _gameState = ShowingMenu;
        break;
    }
    case (PauseScreen::Save):
    {
        std::ofstream os;
        os.open("./save.txt", std::ios::out);
        os << tempspeed << " "
           << dinosaur.GetPosition().x << " " << dinosaur.GetPosition().y << " "
           << background.GetPosition().x << " " << background.GetPosition().y << " "
           << cactus.GetPosition().x << " " << cactus.GetPosition().y << " "
           << cloud1.GetPosition().x << " " << cloud1.GetPosition().y << " "
           << cloud2.GetPosition().x << " " << cloud2.GetPosition().y << " "
           << cloud3.GetPosition().x << " " << cloud3.GetPosition().y << " "
           << bird.GetPosition().x << " " << bird.GetPosition().y << ' '
           << dinosaur.Get_y_v() << ' ' << std::endl;
        os.close();
        *background.GetSpeed() = tempspeed;
        *cactus.GetSpeed() = tempspeed;
        *bird.GetSpeed() = tempspeed;
        *cloud1.GetSpeed() = tempspeed;
        *cloud2.GetSpeed() = tempspeed;
        *cloud3.GetSpeed() = tempspeed;
        _gameState = ShowPauseScreen;

        break;
    }
    case (PauseScreen::Set):
    {
        _gameState = ShowingSetting;
        break;
    }
    case (PauseScreen::Exit):
    {
        _gameState = Exiting;
        break;
    }
    }
}
