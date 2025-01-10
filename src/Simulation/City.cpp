#include <iostream>

#include "City.hpp"
#include "Math.hpp"
#include "../Settings.hpp"

City::City()
{
	sf::Vector2f caseSize = Settings::screen_size / Settings::city_size;
	building.reserve(Settings::city_size.x * Settings::city_size.y);

	//Generate uniform points
	for (size_t y = 0; y < Settings::city_size.y; y++)
	{
		for (size_t x = 0; x < Settings::city_size.x; x++)
		{
			building.push_back(Building(Math::random(
				x * caseSize.x, (x + 1) * caseSize.x,
				y * caseSize.y, (y + 1) * caseSize.y
			)));
		}
	}

	gridLines = sf::VertexArray(sf::PrimitiveType::Lines);	
	for (size_t y = 0; y < Settings::city_size.y + 1; y++)
	{
		for (size_t x = 0; x < Settings::city_size.x + 1; x++)
		{
			//Horizontal line
			gridLines.append(sf::Vertex(sf::Vector2f(0, y * caseSize.y)));
			gridLines.append(sf::Vertex(sf::Vector2f(Settings::screen_size.x, y * caseSize.y)));
			
			//Vertical line
			gridLines.append(sf::Vertex(sf::Vector2f(x * caseSize.x, 0)));
			gridLines.append(sf::Vertex(sf::Vector2f(x * caseSize.x, Settings::screen_size.y)));
		}
	}

	//Generate voronoi
	/*
	img.create(Settings::screen_size.x, Settings::screen_size.y);
	for (int y = 0; y < Settings::screen_size.y; y++)
	{
		for (int x = 0; x < Settings::screen_size.x; x++)
		{
			sf::Vector2i index(x / caseSize.x, y / caseSize.y);
			float neareast = std::numeric_limits<float>::max();
			sf::Vector2i targetIndex;
			
			for (int v = -1; v < 2; v++)
			{
				for (int h = -1; h < 2; h++)
				{
					sf::Vector2i nIndex = index + sf::Vector2i(h, v);
					if (nIndex.x < 0 || nIndex.y < 0 || nIndex.x >= Settings::city_size.x || nIndex.y >= Settings::city_size.y)
					{
						continue;
					}

					float distance = Math::distance(building[nIndex.y * Settings::city_size.x + nIndex.x].position, sf::Vector2f(x, y));
					if (neareast > distance)
					{
						neareast = distance;
						targetIndex = nIndex;
					}
				}
			}		

			img.setPixel(x, y, building[targetIndex.y * Settings::city_size.y + targetIndex.x].color);		
		}
	}
	t.loadFromImage(img);
	s.setTexture(t);
	*/

	generateRoad();
}

void City::generateRoad()
{
	//Generate road lines
	for (size_t y = 0; y < Settings::city_size.y; y += 2)
	{
		for (size_t x = 0; x < Settings::city_size.x; x += 2)
		{
			int index = y * Settings::city_size.x + x;

			for (int v = -1; v < 2; v++)
			{
				for (int h = -1; h < 2; h++)
				{
					int nIndex = (y + v) * Settings::city_size.x + x + h;
					if (nIndex < 0 || nIndex >= building.size() || (v == 0 && h == 0))
					{
						continue;
					}

					sf::Vector2f dir = building[nIndex].position - building[index].position;

					sf::VertexArray roadLine(sf::PrimitiveType::Lines);
					roadLine.append(sf::Vertex(building[index].position, sf::Color::Red));
					roadLine.append(sf::Vertex(building[index].position + sf::Vector2f(dir.x, 0), sf::Color::Red));

					roadLine.append(sf::Vertex(building[index].position + sf::Vector2f(dir.x, 0), sf::Color::Red));
					roadLine.append(sf::Vertex(building[index].position + dir, sf::Color::Red));

					roads.push_back(roadLine);
				}
			}
		}
	}

	//Compute inter road intersection
	for (size_t i = 0; i < roads.size(); i++)
	{
		for (size_t j = 0; j < roads.size(); j++)
		{
			if (i == j)
			{
				continue;
			}

			sf::Vector2f intersectionPosition;
			if (Math::lineIntersect(roads[i][0].position, roads[i][1].position, roads[j][2].position, roads[j][3].position, &intersectionPosition))
			{
				sf::RectangleShape rect(sf::Vector2f(2, 2));
				rect.setPosition(intersectionPosition - sf::Vector2f(1, 1));
				rect.setFillColor(sf::Color::Blue);
				intersections.push_back(rect);
			}
		}
	}

	//Compute self road intersection
	for (size_t i = 0; i < roads.size(); i++)
	{
		sf::Vector2f intersectionPosition;
		if (Math::lineIntersect(roads[i][0].position, roads[i][1].position, roads[i][2].position, roads[i][3].position, &intersectionPosition))
		{
			sf::RectangleShape rect(sf::Vector2f(2, 2));
			rect.setPosition(intersectionPosition - sf::Vector2f(1, 1));
			rect.setFillColor(sf::Color::Blue);
			intersections.push_back(rect);
		}
	}

	//Create graph with nodes

}