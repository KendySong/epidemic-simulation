#include "Node.hpp"

Node::Node(sf::Vector2f position, Building* building)
{
	this->position = position;
	this->building = building;
}