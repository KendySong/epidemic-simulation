#pragma once
#include <cstdint>
#include <SFML/Graphics.hpp>

class Settings
{
public :
    static Settings instance;
    static const std::uint32_t width;
    static const std::uint32_t height;
    static const sf::Vector2f  screen_size;


    static float sensitivity;


private :
    Settings();
};