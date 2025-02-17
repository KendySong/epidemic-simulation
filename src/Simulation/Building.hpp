#pragma once
#include <vector>

#include <SFML/Graphics.hpp>

#include "Node.hpp"

class Building
{
public :
	Building() = default;
	Building(sf::Vector2f position);
	void setTexture();

	Node* node;
	sf::Vector2f position;
	sf::RectangleShape rect;
	sf::Texture texture;
	sf::Color color;

	std::vector<Building*> links;
	
private :
};