#pragma once
#include <SFML/Graphics.hpp>

class Building
{
public :
	Building() = default;
	Building(sf::Vector2f position);

	sf::Vector2f position;
	sf::RectangleShape rect;
	sf::Color color;

private :


};