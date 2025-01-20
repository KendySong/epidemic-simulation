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
	std::map<int, int> builLink;

	sf::Sprite s;
	sf::Texture t;
	sf::Image img;
	

private :
	void generateRoad();
	bool City::linkExist(std::map<int, int> links, int id);
};