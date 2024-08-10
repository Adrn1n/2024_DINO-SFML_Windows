#include "../include/stdafx.h"
#include "../include/MainMenu.h"
#include "../include/ServiceLocator.h"
#include "../include/Settings.h"

// 定义静态成员
std::list<Button> MainMenu::Buttons;
std::list<Button> MainMenu::DifficultyButtons;

sf::Texture MainMenu::backgroundTexture;
sf::Sprite MainMenu::backgroundSprite;
sf::Texture MainMenuDifficultyTexture;
sf::Sprite MainMenuDifficultySprite;
MainMenu::MenuState MainMenu::menuState = MAIN_MENU1;

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow &window)
{
    Buttons.clear();
    // 获取窗口大小
    sf::Vector2u windowSize = window.getSize();
    sf::View WindowView = window.getView();

    // Load menu background from file
    backgroundTexture.loadFromFile("./assets/image/Mainmenu.png");
    backgroundSprite.setTexture(backgroundTexture);
    float scaleX = static_cast<float>(windowSize.x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(windowSize.y) / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);

    // MainMenuBGM
    ServiceLocator::GetAudio()->PlaySong("./assets/audio/MainMenu.ogg", true, Settings::getSongVolume());
    // Setup clickable regions(按钮的位置以中心为坐标)
    float ButtonWidth = windowSize.x / 10.0;
    float ButtonHeight = windowSize.y / 10.0;
    float ButtonX = 0;
    float ButtonY = 0;
    float ButtonDis = 100;

    // Play button coordinates
    Button PlayButton(WindowView, ButtonX, ButtonY, ButtonWidth, ButtonHeight, "Play");
    // 菜单二的按钮
    // New menu item coordinates

    // Set button coordinates
    Button SetButton(WindowView, ButtonX, ButtonY + ButtonDis, ButtonWidth, ButtonHeight, "Set");
    // Exit button coordinates
    Button ExitButton(WindowView, ButtonX, ButtonY + 2 * ButtonDis, ButtonWidth, ButtonHeight, "Exit");
    // Load button coordinates
    Button LoadButton(WindowView, ButtonX, ButtonY + 3 * ButtonDis, ButtonWidth, ButtonHeight, "Load");
    // Easy button coordinates
    Button EasyButton(WindowView, ButtonX, ButtonY, ButtonWidth, ButtonHeight, "Easy");
    // Normal button coordinates
    Button NormalButton(WindowView, ButtonX, ButtonY + ButtonDis, ButtonWidth, ButtonHeight, "Normal");
    // Hard button coordinates
    Button HardButton(WindowView, ButtonX, ButtonY + 2 * ButtonDis, ButtonWidth, ButtonHeight, "Hard");

    // 菜单二的按钮
    // New menu item coordinates

    Buttons.push_back(PlayButton);
    Buttons.push_back(SetButton);
    Buttons.push_back(ExitButton);
    Buttons.push_back(LoadButton);

    DifficultyButtons.push_back(EasyButton);
    DifficultyButtons.push_back(NormalButton);
    DifficultyButtons.push_back(HardButton);

    // Show MainMenu
    window.clear();
    window.draw(backgroundSprite);
    DrawMenu(window, WindowView);
    window.display();

    sf::Event menuEvent;

    while (1)
    {
        while (window.pollEvent(menuEvent))
        {
            window.clear();
            window.draw(backgroundSprite);
            if (menuState == MAIN_MENU1 || menuState == MAIN_MENU2)
            {
                switch (menuEvent.type)
                {
                case (sf::Event::MouseButtonPressed):
                {
                    std::string ButtonName = Button::getClickButtonName(sf::Mouse::getPosition(window), Buttons);
                    if (ButtonName == "Exit")
                        return Exit;
                    else if (ButtonName == "Play")
                    {
                        menuState = DIFFICULTY_SELECTION;
                    }
                    else if (ButtonName == "Set")
                        return Setting;
                    else if (ButtonName == "Load")
                        return Loading;
                    break;
                }
                case (sf::Event::Closed):
                    return Exit;
                }
                DrawMenu(window, WindowView);
            }
            else if (menuState == DIFFICULTY_SELECTION)
            {
                switch (menuEvent.type)
                {
                case (sf::Event::MouseButtonPressed):
                {
                    std::string ButtonName = Button::getClickButtonName(sf::Mouse::getPosition(window), DifficultyButtons);
                    if (ButtonName == "Easy")
                        return Easy;
                    else if (ButtonName == "Normal")
                        return Normal;
                    else if (ButtonName == "Hard")
                        return Hard;
                    break;
                }
                case (sf::Event::KeyPressed):
                {
                    if (menuEvent.key.code == sf::Keyboard::Escape)
                        menuState = MAIN_MENU1;
                    break;
                }
                case (sf::Event::Closed):
                    return Exit;
                }

                DrawDifficulty(window, WindowView);
            }
            window.display();
        }
    }
}

void MainMenu::DrawMenu(sf::RenderWindow &window, sf::View &view)
{
    for (std::list<Button>::iterator i = Buttons.begin(); i != Buttons.end(); i++)
    {
        i->draw(window, view);
    }
}

void MainMenu::DrawDifficulty(sf::RenderWindow &window, sf::View &view)
{
    for (std::list<Button>::iterator i = DifficultyButtons.begin(); i != DifficultyButtons.end(); i++)
    {
        i->draw(window, view);
    }
}
