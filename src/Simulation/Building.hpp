#pragma once
#include <SFML/Graphics.hpp>

class Building
{
public :
	Building() = default;
	Building(int id, sf::Vector2f position);

	int id;
	sf::Vector2f position;
	sf::RectangleShape rect;
	sf::Color color;

private :


};