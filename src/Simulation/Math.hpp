#pragma once
#include <SFML/Graphics.hpp>

class Math
{
public :
	static sf::Vector2f toVec2f(const sf::Vector2i& a);
	static float length(const sf::Vector2f& a);
	static float distance(const sf::Vector2f& a, const sf::Vector2f& b);
	static sf::Vector2f unit(const sf::Vector2f& a);
	static sf::Vector2f random(float xMin, float xMax, float yMin, float yMax);
	static int random(int min, int max);
	static sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float t);
	static float dot(sf::Vector2f a, sf::Vector2f b);
	static bool lineIntersect(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d, sf::Vector2f* o);
};

sf::Vector2f operator+(const sf::Vector2f& a, const sf::Vector2i& b);
sf::Vector2f operator/(const sf::Vector2f& a, const sf::Vector2f& b);