#pragma once
#include <vector>

#include <SFML/Graphics.hpp>

#include "Building.hpp"

class Node
{
public :
	Node(sf::Vector2f position, Building* building = nullptr);
	std::vector<Node*> nodes;

	sf::Vector2f position;
	Building* building;


private :


};