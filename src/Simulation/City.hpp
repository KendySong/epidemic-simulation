#pragma once
#include <vector>
#include <map>

#include <SFML/Graphics.hpp>

#include "Road.hpp"
#include "Human.hpp"
#include "Building.hpp"

class City
{
public :
	City();

	std::vector<Human> humans;
	std::vector<Building> building;
	std::vector<Road> roads;
	
	sf::VertexArray gridLines;
	std::vector<sf::RectangleShape> intersections;

private :
	std::vector<Node> m_nodes;

	void generateRoad();
	bool linkExist(const Building& building, Building* target);
	int intersectionExist(const sf::Vector2f& pos);
};