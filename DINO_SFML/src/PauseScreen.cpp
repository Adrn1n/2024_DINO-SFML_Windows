#include "../include/stdafx.h"
#include "../include/PauseScreen.h"
#include "../include/ServiceLocator.h"
#include "../include/Settings.h"

std::list<Button> PauseScreen::Buttons;

sf::Texture PauseScreen::backgroundTexture;
sf::Sprite PauseScreen::backgroundSprite;

PauseScreen::PauseResult PauseScreen::Show(sf::RenderWindow &window)
{
    // 获取窗口大小
    sf::Vector2u windowSize = window.getSize();
    sf::View WindowView = window.getView();

    // Load menu background from file
    backgroundTexture.loadFromFile("./assets/image/PauseScreen.png");
    backgroundSprite.setTexture(backgroundTexture);
    float scaleX = static_cast<float>(windowSize.x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(windowSize.y) / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);
    // Pause界面不加声音
    ServiceLocator::GetAudio()->PauseSong();
    // Setup clickable regions(按钮的位置以中心为坐标)
    float ButtonWidth = windowSize.x / 10.0;
    float ButtonHeight = windowSize.y / 10.0;
    float ButtonX = 0;
    float ButtonY = -(int)windowSize.y / 4;
    float ButtonDis = 100;

    // Resume button coordinates
    Button ResumeButton(WindowView, ButtonX, ButtonY + 0 * ButtonDis, ButtonWidth, ButtonHeight, "Resume");
    // Restart button coordinates
    Button RestartButton(WindowView, ButtonX, ButtonY + 1 * ButtonDis, ButtonWidth, ButtonHeight, "Restart");
    // Save button coordinates
    Button SaveButton(WindowView, ButtonX, ButtonY + 2 * ButtonDis, ButtonWidth, ButtonHeight, "Save");
    // Set button coordinates
    Button SetButton(WindowView, ButtonX, ButtonY + 3 * ButtonDis, ButtonWidth, ButtonHeight, "Set");
    // Exit button coordinates
    Button ExitButton(WindowView, ButtonX, ButtonY + 4 * ButtonDis, ButtonWidth, ButtonHeight, "Exit");

    Buttons.push_back(ResumeButton);
    Buttons.push_back(RestartButton);
    Buttons.push_back(SaveButton);
    Buttons.push_back(SetButton);
    Buttons.push_back(ExitButton);

    // Show MainMenu
    sf::Event event;
    // 循环
    while (1)
    {

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                return Exit;
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                std::string ButtonName = Button::getClickButtonName(sf::Mouse::getPosition(window), Buttons);
                if (ButtonName == "Resume")
                    return Resume;
                else if (ButtonName == "Restart")
                    return Restart;
                else if (ButtonName == "Save")
                    return Save;
                else if (ButtonName == "Set")
                    return Set;
                else if (ButtonName == "Exit")
                    return Exit;
            }
            window.clear();
            window.draw(backgroundSprite);
            DrawPause(window, WindowView);
            window.display();
        }
    }
}

void PauseScreen::DrawPause(sf::RenderWindow &window, sf::View &view)
{
    for (std::list<Button>::iterator i = Buttons.begin(); i != Buttons.end(); i++)
    {
        i->draw(window, view);
    }
}
