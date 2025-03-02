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
    static const float home_repartition;
    static const float work_repartition;
    static const float entertainment_repartition;
    static const std::uint32_t human_per_home;

    //Simulation
    static const int    start_time;
    static float        speed;
    static float        tempMin;
    static float        temp;
    static float        tempMax;

    static int          stayAtHomeProb;
    static float        avgHumanSpeed;

    static const int    max_health;
    static int          minRandomHealth;

    //Dease
    static float        mortality;
    static int          nbStartInfectHuman;
    static float        aInfectiousness;
    static const int    limit_infection_random;
    static bool         everyoneWashHand;
    static bool         everyoneWearMask;
    static float        nearDistanceHuman;

private :
    Settings();
};