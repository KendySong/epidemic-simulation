#include "City.hpp"
#include "Math.hpp"

City::City()
{
	for (size_t i = 0; i < 5; i++)
	{
		homes.emplace_back(Building(Math::random(-1000, 1000, -1000, 1000)));
	}
}