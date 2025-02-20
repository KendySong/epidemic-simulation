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
	Human(Building* home, std::vector<Building*>* entertainments);
	void draw(sf::RenderTarget& renderTarget);
	Activities findCurrentAction(int hourInDay);
	void update(int hourInDay, float dt);

	std::map<std::pair<int, int>, Activities> lifeSchedule;
	std::vector<Building*>* entertainments;
	Building* home;
	Building* work;
	Building* current;

	float health;
	float speed;
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
	void moveToTarget(Building* target, float dt);

	bool m_isMoving;
	Node* p_targetNode;
	int m_indexNode;
	std::vector<Node*> m_path;
};