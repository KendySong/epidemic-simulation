#pragma once
#include <SFML/Graphics.hpp>

class Math
{
public :
	static sf::Vector2f toVec2f(const sf::Vector2i& a);
	static float length(const sf::Vector2f& a);
	static sf::Vector2f unit(const sf::Vector2f& a);
	static sf::Vector2f random(float xMin, float xMax, float yMin, float yMax);
};

sf::Vector2f operator+(const sf::Vector2f& a, const sf::Vector2i& b);