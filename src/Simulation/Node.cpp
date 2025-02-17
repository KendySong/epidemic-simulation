#include "Node.hpp"

Node::Node(sf::Vector2f position)
{
	this->position = position;
}

void Node::createLink(Node* a, Node* b)
{
	a->links.push_back(b);
	b->links.push_back(a);
}