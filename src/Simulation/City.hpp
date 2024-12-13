#pragma once
#include <vector>

#include "Human.hpp"
#include "Building.hpp"

class City
{
public :
	City();

	std::vector<Human> humans;
	std::vector<Building> building;

private :
	bool superpose();
};