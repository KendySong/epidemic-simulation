#include <limits>
#include <iostream>

#include "City.hpp"
#include "Math.hpp"
#include "Node.hpp"
#include "../Settings.hpp"

City::City()
{	
	//Reserve memory
	m_caseSize = Settings::screen_size / Settings::city_size;
	building.reserve(Settings::city_size.x * Settings::city_size.y);
	m_nodes.reserve(pow(Settings::city_size.x * Settings::city_size.y, 4));

	//Generate rect for heatmap
	heatMap.reserve(building.size());
	heatMapColor.reserve(building.size());

	//Generate building emplacements
	for (size_t y = 0; y < Settings::city_size.y; y++)
	{
		for (size_t x = 0; x < Settings::city_size.x; x++)
		{
			int index = y * Settings::city_size.x + x;
			heatMapColor.emplace_back(m_caseSize);
			heatMapColor[index].setPosition(sf::Vector2f(x * m_caseSize.x, y * m_caseSize.y));


			m_nodes.emplace_back();
			Building build = Building(Math::random(
				x * m_caseSize.x, (x + 1) * m_caseSize.x,
				y * m_caseSize.y, (y + 1) * m_caseSize.y
			));
			build.node = &m_nodes[m_nodes.size() - 1];
			building.push_back(build);
			m_nodes[m_nodes.size() - 1].building = &building[building.size() - 1];
			m_nodes[m_nodes.size() - 1].position = build.position;

			building[building.size() - 1].setType(Type::Undefined);
		}
	}

	//Construct the city
	generateGrid();
	generateRoad();
	
	//Set repartition
	homeRepartition = Settings::home_repartition * building.size();
	workRepartition = Settings::work_repartition * building.size();
	entertainmentRepartition = Settings::home_repartition * building.size();
	entertainmentRepartition += (building.size() - homeRepartition - workRepartition - entertainmentRepartition);

	//Reserve place for humans and sort building
	humans.reserve(Settings::human_per_home * homeRepartition);
	entertainmentPlace.reserve(entertainmentRepartition);
	workPlace.reserve(workRepartition);
	
	//Set which type is which building
	setBuildType(Type::Home, homeRepartition);
	setBuildType(Type::Work, workRepartition);
	setBuildType(Type::Entertainment, entertainmentRepartition);

	//Give work to all humans
	for (size_t i = 0; i < humans.size(); i++)
	{
		humans[i].work = workPlace[Math::random(0, workPlace.size()-1)];
	}
}

void City::updateHeatMap()
{
	heatMap = std::vector<int>(building.size(), 0);
	for (size_t i = 0; i < humans.size(); i++)
	{
		sf::Vector2f caseEmplacement = humans[i].position / m_caseSize;
		int index = (int)caseEmplacement.y * Settings::city_size.x + (int)caseEmplacement.x;
		if (index >= 0 && index < building.size())
		{
			heatMap[index]++;
		}
		
	}

	//Find min and max values
	int min = std::numeric_limits<int>::max();
	int max = std::numeric_limits<int>::min();
	for (size_t i = 0; i < heatMap.size(); i++)
	{
		if (min > heatMap[i])
		{
			min = heatMap[i];
		}

		if (max < heatMap[i])
		{
			max = heatMap[i];
		}
	}

	for (size_t y = 0; y < Settings::city_size.y; y++)
	{
		for (size_t x = 0; x < Settings::city_size.x; x++)
		{
			int index = y * Settings::city_size.x + x;
			float t = Math::alerp(min, max, heatMap[index]);


			sf::Vector3f c = Math::lerp(sf::Vector3f(40, 225, 40), sf::Vector3f(225, 40, 40), t);
			heatMapColor[index].setFillColor(sf::Color(c.x, c.y, c.z, 150));
		}
	}

}

void City::setBuildType(Type type, int quantity)
{
	while (quantity > 0)
	{
		Building* build = &building[Math::random(0, building.size()-1)];
		if (build->type == Type::Undefined)
		{
			build->setType(type);
			quantity--;

			switch (type)
			{
			case Type::Home:
				for (size_t i = 0; i < Settings::human_per_home; i++)
				{
					humans.emplace_back(build, &entertainmentPlace);
				}
				break;

			case Type::Work:
				workPlace.push_back(build);
				break;

			case Type::Entertainment:
				entertainmentPlace.push_back(build);
				break;
			}
		}	
	}
}

void City::generateGrid()
{
	//Generate grid
	gridLines = sf::VertexArray(sf::PrimitiveType::Lines);
	for (size_t y = 0; y < Settings::city_size.y + 1; y++)
	{
		for (size_t x = 0; x < Settings::city_size.x + 1; x++)
		{
			//Horizontal line
			gridLines.append(sf::Vertex(sf::Vector2f(0, y * m_caseSize.y)));
			gridLines.append(sf::Vertex(sf::Vector2f(Settings::screen_size.x, y * m_caseSize.y)));

			//Vertical line
			gridLines.append(sf::Vertex(sf::Vector2f(x * m_caseSize.x, 0)));
			gridLines.append(sf::Vertex(sf::Vector2f(x * m_caseSize.x, Settings::screen_size.y)));
		}
	}

}

void City::generateRoad()
{
	//Generate road lines
	roadVertices = sf::VertexArray(sf::PrimitiveType::Lines);
	for (int y = 0; y < Settings::city_size.y; y += 2)
	{
		for (int x = 0; x < Settings::city_size.x; x += 2)
		{
			int index = y * Settings::city_size.x + x;
			for (int v = -1; v < 2; v++)
			{
				for (int h = -1; h < 2; h++)
				{		
					int nIndex = (y + v) * Settings::city_size.x + x + h;
					if (h == v || (h == -1 && x == 0) || (h == 1 && x == Settings::city_size.x-1) || nIndex < 0 || nIndex >= building.size() || linkExist(building[index], &building[nIndex]))
					{
						continue;
					}

					sf::Vector2f dir = building[nIndex].position - building[index].position;

					Road road(&building[index], &building[nIndex]);
					road.lines = sf::VertexArray(sf::PrimitiveType::Lines);

					roadVertices.append(sf::Vertex(building[index].position, sf::Color::Red));
					roadVertices.append(sf::Vertex(building[index].position + dir, sf::Color::Red));

					road.lines.append(sf::Vertex(building[index].position, sf::Color::Red));
					road.lines.append(sf::Vertex(building[index].position + dir, sf::Color::Red));

					building[index].links.push_back(&building[nIndex]);
					building[nIndex].links.push_back(&building[index]);

					roads.push_back(road);
					Node::createLink(building[index].node, building[nIndex].node);
				}
			}
		}
	}

	//Compute inter road intersection and generate graph
	for (size_t i = 0; i < roads.size(); i++)
	{
		for (size_t j = 0; j < roads.size(); j++)
		{
			if (i == j) continue;
			sf::Vector2f intersectionPosition;
			if (Math::lineIntersect(roads[i].lines[0].position, roads[i].lines[1].position, roads[j].lines[0].position, roads[j].lines[1].position, &intersectionPosition))
			{
				bool onBuilding = false;
				for (size_t i = 0; i < building.size(); i++)
				{
					if (Math::distance(intersectionPosition, building[i].position) <= 0.001)
					{
						onBuilding = true;
						break;
					}
				}

				//Check if the intersection not exist
				if (intersectionExist(intersectionPosition) == -1 && !onBuilding)
				{
					//Create blue rect for display intersection
					sf::RectangleShape rect(sf::Vector2f(5, 5));
					rect.setPosition(intersectionPosition - sf::Vector2f(1, 1));
					rect.setFillColor(sf::Color::Yellow);
					intersections.push_back(rect);

					m_nodes.emplace_back();
					Node* intersection = &m_nodes[m_nodes.size() - 1];
					intersection->position = intersectionPosition;
					Node::createLink(intersection, roads[i].a->node);
					Node::createLink(intersection, roads[i].b->node);
					Node::createLink(intersection, roads[j].a->node);
					Node::createLink(intersection, roads[j].b->node);
					
					for (size_t k = 0; k < roads[i].intersections.size(); k++)
							Node::createLink(intersection, roads[i].intersections[k]);
					for (size_t k = 0; k < roads[j].intersections.size(); k++)
							Node::createLink(intersection, roads[j].intersections[k]);		
					roads[i].intersections.push_back(intersection);
					roads[j].intersections.push_back(intersection);
				}		
			}
		}
	}
}

bool City::linkExist(const Building& building, Building* target)
{
	for (size_t i = 0; i < building.links.size(); i++)
		if (building.links[i] == target)
			return true;
	return false;
}

int City::intersectionExist(const sf::Vector2f& pos)
{
	for (size_t i = 0; i < intersections.size(); i++)
		if (pos == intersections[i].getPosition() + sf::Vector2f(1, 1))
			return i;
	return -1;
}