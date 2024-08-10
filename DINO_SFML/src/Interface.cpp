#include "../include/Interface.h"
#include "../include/ServiceLocator.h"
#include "../include/Game.h"

sf::Vector2f changeV2itoV2f(sf::Vector2i vec)
{
    return sf::Vector2f((int)vec.x, (int)vec.y);
}
sf::Vector2i changeV2ftoV2i(sf::Vector2f vec)
{
    return sf::Vector2i((float)vec.x, (float)vec.y);
}
sf::Vector2i getMousePosition(sf::RenderWindow &window)
{
    sf::Vector2f windowPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    //	std::printf("MOUSE: %d %d\n", (int)windowPos.x, (int)windowPos.y);
    return sf::Vector2i((int)windowPos.x, (int)(windowPos.y));
}

Button::Button(const sf::View &view, float x, float y, float width, float height, const std::string &text)
{
    // 记录创建按钮时的信息，方便后续更新按钮
    originalView = view;
    originalPosition.x = x;
    originalPosition.y = y;
    originalSize.x = width;
    originalSize.y = height;
    // 获取视图信息，设置按钮矩形的大小，并把原点设为中心
    sf::Vector2f center = view.getCenter();
    shape.setSize(sf::Vector2f(width, height));
    setOriginToCenter(shape);
    // 设置按钮位置
    shape.setPosition(x + center.x, y + center.y);

    // 设置按钮文本内容
    font.loadFromFile("./assets/font/pixel_title.ttf");
    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::Black);
    // 设置文本位置
    setOriginToCenter(buttonText);
    buttonText.setPosition(x + center.x, y + center.y);

    // 设置按钮颜色
    originalColor = sf::Color::White;
    shape.setFillColor(sf::Color::White);

    wasPutOn = false;
}

std::string Button::getClickButtonName(sf::Vector2i clickPosition, std::list<Button> &Buttons)
{
    for (Button &button : Buttons)
        if (button.isClicked(clickPosition))
        {
            ServiceLocator::GetAudio()->PlaySound("./assets/audio/Button.flac");
            return button.buttonText.getString();
        }
    return "";
}

void Button::draw(sf::RenderWindow &window, const sf::View &view)
{
    updateAppearance(window, view);
    window.draw(shape);
    window.draw(buttonText);
}

bool Button::isClicked(sf::Vector2i mousePos)
{
    return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

bool Button::isPutOn(sf::Vector2i mousePos)
{
    return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void Button::updateAppearance(sf::RenderWindow &window, const sf::View &view)
{
    // 根据视图改变按钮和的大小、位置
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();
    float xratio = viewSize.x / originalView.getSize().x;
    float yratio = viewSize.y / originalView.getSize().y;
    shape.setPosition(originalPosition.x * xratio + viewCenter.x, originalPosition.y * yratio + viewCenter.y);
    buttonText.setPosition(originalPosition.x * xratio + viewCenter.x, originalPosition.y * yratio + viewCenter.y);
    // 根据鼠标位置更新按钮颜色,以及触发音效
    if (isPutOn(sf::Mouse::getPosition(window)))
    {
        if (!wasPutOn)
        {
            ServiceLocator::GetAudio()->PlaySound("./assets/audio/Button.flac");
            wasPutOn = true;
        }
        shape.setFillColor(sf::Color::Yellow);
    }
    else
    {
        shape.setFillColor(originalColor);
        if (wasPutOn)
            wasPutOn = false;
    }
}

Slider::Slider(const std::string &name, float width, float height, float current_value, float max_value)
    : _name(name), _width(width), _height(height), _max_value(max_value),
      _current_value(current_value), isSliderDragged(false), wasButtonClicked(false), isButtonClicked(false)
{

    // 滑动条背景设置
    _background.setSize(sf::Vector2f(width, height));
    _background.setFillColor(sf::Color(100, 100, 100, 150));
    _background.setOutlineColor(sf::Color::Black);
    _background.setOutlineThickness(_thickness);
    setOriginToLeft(_background);

    // 滑动条设置
    _current_slider.setSize(sf::Vector2f(width * current_value / max_value, height));
    _current_slider.setFillColor(sf::Color::Blue);
    setOriginToLeft(_current_slider);

    // 可按方块设置
    _button.setSize(sf::Vector2f(height, height));
    if (current_value == 0)
        _button.setFillColor(sf::Color::Red);
    else
        _button.setFillColor(sf::Color::Green);
    _button.setOutlineColor(sf::Color::Black);
    _button.setOutlineThickness(_thickness);
    setOriginToLeft(_button);

    // 滑动条名字文本设置
    if (!_font.loadFromFile("./assets/font/pixel.ttf"))
    {
        // handle error
    }
    _nameText.setFont(_font);
    _nameText.setString(name);
    _nameText.setCharacterSize(height);
    _nameText.setFillColor(sf::Color::Yellow);
    _nameText.setStyle(sf::Text::Bold);
    setOriginToLeft(_nameText);
}

// 获得滑动条的值
float Slider::getValue() const
{
    return _current_value;
}

// 改变滑动条当前值
void Slider::setValue(float current_value)
{
    _current_value = current_value;
}

// 基于视图的位置设置，x和y为滑动条对象的左中点
void Slider::setPosition(const sf::View &view, float x, float y)
{
    sf::Vector2f ViewCenter = view.getCenter();
    float Dis = view.getSize().x / 50;
    // 根据视图确定滑动条位置
    _nameText.setPosition(x + ViewCenter.x, y + ViewCenter.y);
    _button.setPosition(_nameText.getPosition().x + _nameText.getGlobalBounds().width + Dis, y + ViewCenter.y);
    _current_slider.setPosition(_button.getPosition().x + _button.getSize().x + Dis, y + ViewCenter.y);
    _background.setPosition(_current_slider.getPosition());
}

// 检测鼠标按下的位置
void Slider::detectPressMouse(sf::RenderWindow &window)
{
    sf::Vector2i mousePosition = getMousePosition(window);
    if (_background.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
        isSliderDragged = true;
    if (_button.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
        isButtonClicked = true;
}

// 拖动滑动条
void Slider::follow(sf::RenderWindow &window)
{
    sf::Vector2i mousePosition = getMousePosition(window);
    if (0.0 <= mousePosition.x - _current_slider.getPosition().x && mousePosition.x - _current_slider.getPosition().x <= _width)
        updateSlider(mousePosition.x - _current_slider.getPosition().x);
}

// 绘制滑动条
void Slider::draw(sf::RenderWindow &window, sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        detectPressMouse(window);
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        isSliderDragged = false;
        isButtonClicked = false;
        wasButtonClicked = false;
    }
    if (isButtonClicked == true)
    {
        if (!wasButtonClicked)
        {
            if (_button.getFillColor() == sf::Color::Green)
            {
                _button.setFillColor(sf::Color::Red);
                wasButtonClicked = true;
                updateSlider(0);
            }
            else
            {
                _button.setFillColor(sf::Color::Green);
                wasButtonClicked = true;
                updateSlider(_width);
            }
        }
    }
    if (isSliderDragged)
        follow(window);
    window.draw(_background);
    window.draw(_current_slider);
    window.draw(_button);
    window.draw(_nameText);
}

sf::FloatRect Slider::getGlobalBounds() const
{
    return _background.getGlobalBounds();
}

// 更新滑动条的长度和值
void Slider::updateSlider(float length)
{
    _current_slider.setSize(sf::Vector2f(length, _height));
    setValue(length / _width * _max_value);
}
