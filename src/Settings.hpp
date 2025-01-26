#pragma once
#include <cstdint>
#include <SFML/Graphics.hpp>

class Settings
{
public :
    static Settings instance;

    //Window
    static const std::uint32_t width;
    static const std::uint32_t height;
    static const sf::Vector2f  screen_size;
    static const sf::Color clear_color;

    //Controls
    static const float base_zoom;
    static float sensitivity;
    static float zoom;

    //City
    static const float home_size;
    static const sf::Vector2f city_size;

    //Context
    static float tempMin;
    static float tempMax;

private :
    Settings();
};