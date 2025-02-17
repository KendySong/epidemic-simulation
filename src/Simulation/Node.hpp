#pragma once
#include <vector>

#include <SFML/Graphics.hpp>

class Building;

class Node
{
public :
	Node();
	Node(sf::Vector2f position, Building* building = nullptr);
	static void createLink(Node* a, Node* b);
	Building* building;
	std::vector<Node*> links;
	sf::Vector2f position;

private :

};