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

	//Generate road
	for (size_t y = 0; y < Settings::screen_size.y; y++)
	{
		for (size_t x = 0; x < Settings::screen_size.x; x++)
		{
			sf::Vector2f index(x / caseSize.x, y / caseSize.y);
			float minDist = std::numeric_limits<float>::max();

			for (int v = -1; v < 2; v++)
			{
				for (int h = -1; h < 2; h++)
				{
					sf::Vector2f currentIndex(index.x + v, index.y + h);
					if (currentIndex.x < 0 || currentIndex.x >= Settings::city_size.x || currentIndex.y < 0 || currentIndex.y >= Settings::city_size.y)
					{
						return;
					}

					float distance = Math::distance(building[currentIndex.y * Settings::city_size.x + currentIndex.x].position, sf::Vector2f(x, y));
					if (minDist > distance)
					{
						index = currentIndex;
						minDist = distance;
					}
				}
			}


		}
	}
	
}