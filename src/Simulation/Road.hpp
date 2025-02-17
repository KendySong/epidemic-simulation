#pragma once
#include <vector>

#include <SFML/Graphics.hpp>

#include "Node.hpp"
#include "Building.hpp"

class Road
{
public:
    Road(Building* a, Building* b);
    sf::VertexArray lines;
    std::vector<Node*> intersections;
    Building* a;
    Building* b;

private :

};

