#pragma once
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Activities.hpp"
#include "Node.hpp"

class Building;
class Human
{
public :
	Human(Building* home);
	void draw(sf::RenderTarget& renderTarget);
	Activities findCurrentAction(int hourInDay);
	void update(int hourInDay, float dt);

	std::map<std::pair<int, int>, Activities> lifeSchedule;
	Building* home;
	Building* work;
	Building* current;

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
	bool m_isMoving;
	Node* p_targetNode;
	int m_indexNode;
	std::vector<Node*> m_path;
};