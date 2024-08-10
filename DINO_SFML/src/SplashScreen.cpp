#include "../include/stdafx.h"
#include "../include/SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow &renderWindow)
{
    sf::Texture texture;
    if (texture.loadFromFile("./assets/image/SplashScreen.png") != true)
    {
        return;
    }
    sf::Sprite sprite(texture);
    sf::Vector2u windowSize = renderWindow.getSize();
    sf::Vector2u textureSize = texture.getSize();

    // 调整精灵的比例，使其大小与窗口大小相同
    sprite.setScale(
        static_cast<float>(windowSize.x) / textureSize.x,
        static_cast<float>(windowSize.y) / textureSize.y);
    sf::Event event;
    while (renderWindow.isOpen())
    {
        while (renderWindow.pollEvent(event))
        {
            switch (event.type)
            {
            case (sf::Event::Closed):
                renderWindow.close();
                break;
            case (sf::Event::Resized):
            {
                // Adjust the viewport when the window is resized
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                renderWindow.setView(sf::View(visibleArea));

                // Adjust the sprite size or position if necessary
                // Here we scale the sprite to fit the new window size
                sprite.setScale(
                    static_cast<float>(event.size.width) / texture.getSize().x,
                    static_cast<float>(event.size.height) / texture.getSize().y);
                break;
            }
            }
            if (event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::MouseButtonPressed || event.type == sf::Event::EventType::Closed)
            {
                return;
            }
            renderWindow.clear();
            renderWindow.draw(sprite);
            renderWindow.display();
        }
    }
}
