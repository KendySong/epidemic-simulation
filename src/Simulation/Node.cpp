#include "Node.hpp"

Node::Node()
{
	building = nullptr;
}

Node::Node(sf::Vector2f position, Building* building)
{
	this->position = position;
	this->building = building;
}

void Node::createLink(Node* a, Node* b)
{
	a->links.push_back(b);
	b->links.push_back(a);
}