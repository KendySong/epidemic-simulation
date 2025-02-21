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
	void updateHeatMap();

	std::vector<Building> building;
	std::vector<Building*> entertainmentPlace;
	std::vector<Building*> workPlace;
	std::vector<Human> humans;
	std::vector<Road> roads;

	std::vector<int> heatMap;
	std::vector<sf::RectangleShape> heatMapColor;

	//Debug
	sf::VertexArray gridLines;
	std::vector<sf::RectangleShape> intersections;
	sf::VertexArray roadVertices;

	//Info
	int homeRepartition;
	int workRepartition;
	int entertainmentRepartition;

private :
	std::vector<Node> m_nodes;
	sf::Vector2f m_caseSize;

	void setBuildType(Type type, int quantity);
	void generateGrid();
	void generateRoad();
	bool linkExist(const Building& building, Building* target);
	int intersectionExist(const sf::Vector2f& pos);
};