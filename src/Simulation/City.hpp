#pragma once
#include <vector>
#include <map>

#include <SFML/Graphics.hpp>

#include "Human.hpp"
#include "Building.hpp"

class City
{
public :
	City();

	std::vector<Human> humans;
	std::vector<Building> building;
	std::vector<sf::VertexArray> roads;
	sf::VertexArray gridLines;

	std::vector<sf::RectangleShape> intersections;

	/*
	sf::Sprite s;
	sf::Texture t;
	sf::Image img;
	*/

private :

	void generateRoad();
	bool linkExist(const Building& building, Building* target);
	int intersectionExist(const sf::Vector2f& pos);
};