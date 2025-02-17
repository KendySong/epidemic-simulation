#pragma once
#include <vector>

#include <SFML/Graphics.hpp>

#include "Node.hpp"

class Building
{
public :
	Building() = default;
	Building(sf::Vector2f position);

	Node* node;
	sf::Vector2f position;
	sf::RectangleShape rect;
	sf::Color color;

	std::vector<Building*> links;
	
private :
};