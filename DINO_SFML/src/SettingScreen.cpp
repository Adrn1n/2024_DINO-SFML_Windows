#include "../include/SettingScreen.h"
#include "../include/ServiceLocator.h"
#include "../include/Game.h"

// 定义静态成员
sf::Texture SettingScreen::backgroundTexture;
sf::Sprite SettingScreen::backgroundSprite;
std::list<Slider *> SettingScreen::Sliders;
std::list<Button> SettingScreen::Buttons;

SettingScreen::SetResult SettingScreen::Show(sf::RenderWindow &window)
{
    Sliders.clear();
    Buttons.clear();
    // 获取窗口大小
    sf::Vector2u windowSize = window.getSize();
    sf::View WindowView = window.getView();
    sf::Vector2f ViewCenter = WindowView.getCenter();

    // Load menu background from file
    backgroundTexture.loadFromFile("./assets/image/SettingScreen.png");
    backgroundSprite.setTexture(backgroundTexture);
    float scaleX = static_cast<float>(windowSize.x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(windowSize.y) / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);
    // SettingScreenBGM
    ServiceLocator::GetAudio()->PlaySong("./assets/audio/SettingScreen.ogg", true, Settings::getSongVolume());

    // 添加滑块
    float SliderWidth = windowSize.x / 3.0;
    float SliderHeight = windowSize.y / 20.0;
    float SliderX = 0;
    float SliderY = 0;
    float SliderDis = 100;
    float ButtonWidth = windowSize.x / 10.0;
    float ButtonHeight = windowSize.y / 10.0;
    float ButtonX = 0;
    float ButtonY = 0;
    float ButtonDis = 100;
    Slider SongSlider("BGM", SliderWidth, SliderHeight, Settings::getSongVolume());
    SongSlider.setPosition(WindowView, 0, 0);
    Slider SoundSlider("F X", SliderWidth, SliderHeight, 100.f);
    SoundSlider.setPosition(WindowView, 0, SliderDis);
    Sliders.push_back(&SongSlider);
    Sliders.push_back(&SoundSlider);
    // 添加帮助
    Button HelpButton(WindowView, 400, 300, ButtonWidth, ButtonHeight, "Help");
    Buttons.push_back(HelpButton);

    // Show MainMenu
    sf::Event event;
    // 循环
    while (1)
    {

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                return Menu;
            else if (event.type == sf::Event::Closed)
                return Exit;
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                std::string ButtonName = Button::getClickButtonName(sf::Mouse::getPosition(window), Buttons);
                if (ButtonName == "Help")
                    return Help;
            }
            window.clear();
            window.draw(backgroundSprite);
            updateSetItem(window, WindowView, event);
            window.display();
            Settings::setSongVolume(SongSlider.getValue());
            Settings::setSoundVolume(SoundSlider.getValue());
            ServiceLocator::GetAudio()->ChangeSongVolume(Settings::getSongVolume());
            ServiceLocator::GetAudio()->ChangeSoundVolume(Settings::getSoundVolume());
        }
    }
}

void SettingScreen::updateSetItem(sf::RenderWindow &window, sf::View &view, sf::Event &event)
{
    for (std::list<Button>::iterator i = Buttons.begin(); i != Buttons.end(); i++)
    {
        i->draw(window, view);
    }
    for (std::list<Slider *>::iterator i = Sliders.begin(); i != Sliders.end(); i++)
    {
        (*i)->draw(window, event);
    }
}
