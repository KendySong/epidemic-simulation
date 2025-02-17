#include "Settings.hpp"

Settings Settings::instance;

Settings::Settings()
{
    
}

//Window
const std::uint32_t Settings::width  = 1600;
const std::uint32_t Settings::height = 900;
const sf::Vector2f  Settings::screen_size(Settings::width, Settings::height);
const float         Settings::base_zoom = 0.75;
const sf::Color     Settings::clear_color = sf::Color(38, 38, 38);

//Controls
float Settings::sensitivity = Settings::base_zoom;
float Settings::zoom = 1;

//City
const float         Settings::home_size = 5;
const sf::Vector2f  Settings::city_size = sf::Vector2f(29, 15); //x and y component must be odd

//Context
float Settings::tempMin = -5;
float Settings::tempMax = 35;