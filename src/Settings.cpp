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
const float         Settings::home_size = 20;
const sf::Vector2f  Settings::city_size = sf::Vector2f(16, 9);     //x and y component is better when odd
const float Settings::home_repartition = 0.5;                       //Pourcent of building will be set to home
const float Settings::work_repartition = 0.40;
const float Settings::entertainment_repartition = 0.10;             //Sum of repartition must be 1

//Context
float Settings::tempMin = -5;
float Settings::tempMax = 35;