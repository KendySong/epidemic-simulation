#include "Building.hpp"
#include "../Settings.hpp"

Building::Building(sf::Vector2f position)
{
	this->position = position;
	sf::Vector2f homeSize = sf::Vector2f(Settings::home_size, Settings::home_size);
	rect = sf::RectangleShape(homeSize);
	rect.setPosition(position - homeSize*0.5f);
	rect.setFillColor(sf::Color::White);
}