#pragma once
#define _USE_MATH_DEFINES
#define M_PI_6 M_PI / 6
#include <math.h>

#include <SFML/Graphics.hpp>

class Math
{
public :
	static sf::Vector2f toVec2f(const sf::Vector2i& a);
	static float length(const sf::Vector2f& a);
	static float distance(const sf::Vector2f& a, const sf::Vector2f& b);
	static sf::Vector2f normalize(const sf::Vector2f& a);
	static sf::Vector2f random(float xMin, float xMax, float yMin, float yMax);
	static int random(int min, int max);
	static float random(float min, float max);
	static sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float t);
	static float dot(sf::Vector2f a, sf::Vector2f b);
	static bool lineIntersect(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d, sf::Vector2f* o);
	static sf::Vector3f lerp(sf::Vector3f a, sf::Vector3f b, float t);
	static float alerp(float a, float b, float x);
	static float getTemp(float time);
	static float getImmunitary(int age);
};

sf::Color operator*(const sf::Color& a, float t);
sf::Vector2f operator+(const sf::Vector2f& a, const sf::Vector2i& b);
sf::Vector2f operator/(const sf::Vector2f& a, const sf::Vector2f& b);