#include "Math.hpp"

sf::Vector2f Math::toVec2f(const sf::Vector2i& a)
{
	return { (float)a.x, (float)a.y };
}

sf::Vector2f operator+(const sf::Vector2f& a, const sf::Vector2i& b)
{
	return { a.x + b.x, a.y + b.y };
}