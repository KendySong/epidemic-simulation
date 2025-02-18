#pragma once
#include <vector>

#include <SFML/Graphics.hpp>

#include "Node.hpp"
#include "Type.hpp"

class Building
{
public :
	Building() = default;
	Building(sf::Vector2f position);
	void setType(Type type);

	static sf::Texture home;

	sf::Vector2f position;
	Node* node;
	Type type;
	std::vector<Building*> links;

	sf::RectangleShape rect;
	sf::Color color;
private :
};