#include "Settings.hpp"

Settings Settings::instance;

Settings::Settings()
{
    
}

const std::uint32_t Settings::width  = 1280;
const std::uint32_t Settings::height = 720;
const sf::Vector2f  Settings::screen_size(Settings::width, Settings::height);

float Settings::sensitivity = 0.5f;
float Settings::zoom = 1;
