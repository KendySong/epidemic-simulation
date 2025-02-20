#include "Math.hpp"
#include "../Settings.hpp"

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

sf::Vector2f Math::normalize(const sf::Vector2f& a)
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
	return (max - min) * ((float)(rand()) / (float)(RAND_MAX)) + min;
}

float Math::random(float min, float max)
{
	return (max - min) * ((float)rand() / (float)RAND_MAX) + min;
}

sf::Vector2f Math::lerp(sf::Vector2f a, sf::Vector2f b, float t)
{
	return (b - a) * t + a;
}

float Math::dot(sf::Vector2f a, sf::Vector2f b)
{
	return a.x * b.x + a.y * b.y;
}

bool Math::lineIntersect(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d, sf::Vector2f* o)
{
	sf::Vector2f ab = b - a;
	sf::Vector2f cd = d - c;
	sf::Vector2f ac = c - a;

	float det = ab.x * cd.y - cd.x * ab.y;

	if (det == 0)
	{
		return false;
	}
	
	float t1 =  (cd.y  * ac.x - cd.x * ac.y) / det;
	float t2 = -(-ab.y * ac.x + ab.x * ac.y) / det;
	
	
	if (Math::distance(a + ab * t1, c + cd * t2) < 0.001f && (t1 <= 1 && t1 >= 0 && t2 <= 1 && t2 >= 0))
	{
		*o = a + ab * t1;
		return true;
	}
	
	return false;
}

float Math::getTemp(float time)
{
	return ((sin(M_PI_6 * (time - 3)) + 1) / 2.0f) * (Settings::tempMax - Settings::tempMin) + Settings::tempMin;
}

float Math::getImmunitary(int age)
{
	return 30 * cos((age - 25) / 40);
}