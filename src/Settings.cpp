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
float               Settings::sensitivity = Settings::base_zoom;
float               Settings::zoom = 1;

//City
const float         Settings::home_size = 25;
const sf::Vector2f  Settings::city_size = sf::Vector2f(13, 7);              //x and y component is better when odd
const float         Settings::home_repartition = 0.5;                       //Pourcent of building will be set to home
const float         Settings::work_repartition = 0.40;
const float         Settings::entertainment_repartition = 0.10;             //Sum of repartition must be 1
const std::uint32_t Settings::human_per_home = 20;                          

//Simulation
const int           Settings::start_time = 4;
float               Settings::speed   = 1;
float               Settings::tempMin = -5;                                 
float               Settings::temp = 0;
float               Settings::tempMax = 35;                                 //Not greater than 100
int                 Settings::stayAtHomeProb = 3;
float               Settings::avgHumanSpeed = 1000;

const int           Settings::max_health = 100;
int                 Settings::minRandomHealth = 90;                              

//Desease
float               Settings::mortality = 50;
int                 Settings::nbStartInfectHuman = 100;
float               Settings::aInfectiousness = 10;
const int           Settings::limit_infection_random = 100000;
bool                Settings::everyoneWashHand = false;
bool                Settings::everyoneWearMask = false;
float               Settings::nearDistanceHuman = 35;