#pragma once
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Activities.hpp"

class Building;
class Human
{
public :
	Human(Building* home);
	void draw(sf::RenderTarget& renderTarget);
	void update(int hourInDay);

	Building* home;
	Building* work;

	float health;
	sf::CircleShape body;
	sf::Vector2f position;
	bool isInHome;

	float immunitaryLevel;
	float averageSleepTime;
	float qualityLevelFood;
	float riskHumanTimer;
	float riskZoneTimer;
	float sedentaryLevel;
	bool wearMask;
	bool washHand;
	bool isSick;
	int age;

private :
	std::map<std::pair<int, int>, Activities> m_lifeSchedule;
};