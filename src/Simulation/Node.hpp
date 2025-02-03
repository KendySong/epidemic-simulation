#pragma once
#include <vector>

#include <SFML/Graphics.hpp>

class Node
{
public :
	Node() = default;
	Node(sf::Vector2f position);
	
	std::vector<Node*> nodes;
	sf::Vector2f position;

private :
};