#pragma once
#include <SFML/Graphics.hpp>

class Math
{
public :
	static sf::Vector2f toVec2f(const sf::Vector2i& a);
};

sf::Vector2f operator+(const sf::Vector2f& a, const sf::Vector2i& b);