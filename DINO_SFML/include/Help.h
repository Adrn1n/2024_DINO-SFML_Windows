#pragma once

class Help
{
public:
    enum HelpResult
    {
        Setting,
        Exit
    };
    Help::HelpResult Show(sf::RenderWindow &window);
};
