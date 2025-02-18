#pragma once
#include <SFML/Graphics.hpp>

class Texture
{
public :
    static Texture* instance();
    sf::Texture* home;
    sf::Texture* work;
    sf::Texture* entertainment;

private :
    Texture();
    static Texture* s_instance;
};