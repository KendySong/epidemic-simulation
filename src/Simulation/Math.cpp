#include "Math.hpp"

sf::Vector2f Math::toVec2f(const sf::Vector2i& a)
{
	return { (float)a.x, (float)a.y };
}

sf::Vector2f operator+(const sf::Vector2f& a, const sf::Vector2i& b)
{
	return { a.x + b.x, a.y + b.y };
}

sf::Vector2f operator/(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return { a.x / b.x, a.y / b.y };
}

float Math::length(const sf::Vector2f& a)
{
	return sqrt(a.x*a.x + a.y*a.y);
}

float Math::distance(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return Math::length(b - a);
}

sf::Vector2f Math::unit(const sf::Vector2f& a)
{
	return a / Math::length(a);
}

sf::Vector2f Math::random(float xMin, float xMax, float yMin, float yMax)
{
	float tx = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	float ty = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	return { tx * (xMax-xMin) + xMin, ty * (yMax - yMin) + yMin };
}

int Math::random(int min, int max)
{
	return (max - min) * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) + min;
}