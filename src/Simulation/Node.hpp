#pragma once
#include <vector>

#include <SFML/Graphics.hpp>

class Node
{
public :
	Node() = default;
	Node(sf::Vector2f position);
	static void createLink(Node* a, Node* b);

	std::vector<Node*> links;
	sf::Vector2f position;

private :

};