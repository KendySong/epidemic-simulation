#include <iostream>
#include <math.h>

#include "Math.hpp"
#include "Human.hpp"
#include "Building.hpp"
#include "../Settings.hpp"
#include "Pathfinding.hpp"
#include "City.hpp"

Human::Human(Building* home, std::vector<Building*>* entertainments, City* city, int id)
{
	//Rendering and pathfinding
	this->id = id;
	p_city = city;
	this->home = home;
	this->isInfected = false;	
	this->current = home->node;
	this->position = home->position;
	this->p_targetNode = nullptr;
	speed = Math::random(Settings::avgHumanSpeed - Settings::avgHumanSpeed/10, Settings::avgHumanSpeed + Settings::avgHumanSpeed/10);

	this->entertainments = entertainments;
	m_isMoving = false;
	m_indexNode = 1; //Start from 1 for avoid repeatly going on starting node
	m_lastHour = 0;

	body = sf::CircleShape(5);
	body.setPointCount(3);
	body.setFillColor(sf::Color::Green);

	//Create schedules
	int hourToSleep = Math::random(22, 24);
	int hourToWork = Math::random(6, 10);
	int hourToWorkFinish = Math::random(15, 17);

	lifeSchedule[std::pair<int, int>(hourToSleep, 24)] = Activities::Sleep;
	lifeSchedule[std::pair<int, int>(0, hourToWork)] = Activities::Sleep;
	lifeSchedule[std::pair<int, int>(hourToWork + 1, hourToWorkFinish)] = Activities::Work;
	lifeSchedule[std::pair<int, int>(hourToWorkFinish + 1, hourToWorkFinish + 2)] = Activities::Home;
	lifeSchedule[std::pair<int, int>(hourToWorkFinish + 3, hourToSleep - 1)] = Math::random(0, Settings::stayAtHomeProb) == 0 ? Activities::Home : Activities::Entertainment;

	//Disease
	switch (Math::random(0, 5))
	{
	case 0:
		this->age = Math::random(0, 21);
		break;

	case 1:
	case 2:
		this->age = Math::random(21, 60);
		break;

	case 3:
	case 4:
		this->age = Math::random(61, 100);
		break;
	}

	this->health = Math::random(80, 101);
	immunitaryLevel = Math::getImmunitary(this->age);
	infectiousness = 0;
	riskHumanTimer = 0;
	riskZoneTimer  = 0;
}

void Human::draw(sf::RenderTarget& renderTarget)
{
	if (Math::distance(position, current->position) <= 10)
	{
		return;
	}

	body.setPosition(position - sf::Vector2f(body.getRadius(), body.getRadius()));
	body.setFillColor(isInfected ? sf::Color::Red : sf::Color::Green);
	renderTarget.draw(body);
}

Activities Human::findCurrentAction(int hourInDay)
{
	for (const auto& item : lifeSchedule)
	{
		if (hourInDay >= item.first.first && hourInDay <= item.first.second)
		{
			return item.second;
		}
	}
	return Activities::Undefined;
}

void Human::update(int hourInDay, float dt)
{
	//Compute time in infected zone
	for (size_t i = 0; i < p_city->humans.size(); i++)
	{
		if (id != p_city->humans[i].id && Math::distance(position, p_city->humans[i].position) <= Settings::nearDistanceHuman && p_city->humans[i].isInfected)
		{
			riskHumanTimer += dt;
			break;
		}
	}
	
	//Compute time in infected zone
	riskZoneTimer += p_city->getInfectiousness(position) * dt;
	
	//Set if the human will be considered as infected or not
	if (m_lastHour != hourInDay)
	{	
		this->updateInfection();
	}

	switch (findCurrentAction(hourInDay))
	{
	case Activities::Sleep:
		moveToTarget(home, dt);
		//Add hp (max 100)
		break;

	case Activities::Home:
		moveToTarget(home, dt);
		break;

	case Activities::Work:
		moveToTarget(work, dt);
		break;

	case Activities::Entertainment:
		moveToTarget((*entertainments)[Math::random(0, (*entertainments).size()-1)], dt);
		break;
	}

	m_lastHour = hourInDay;
}

void Human::updateInfection()
{
	/*
	if (isInfected)
	{
		//Remove hp
	}
	else
	{
		infectiousness = Settings::temp * (riskHumanTimer + riskZoneTimer) - Settings::everyoneWashHand - Settings::everyoneWearMask - immunitaryLevel;
	}
	*/
}

void Human::moveToTarget(Building* target, float dt)
{
	if (current != target->node && !m_isMoving)
	{
		m_path = Pathfinding::path(current, target->node);
		m_isMoving = true;
	}

	if (m_isMoving && m_path.size() > 0 && m_indexNode < m_path.size())
	{
		if (Math::distance(m_path[m_indexNode]->position, position) <= 10)
		{
			m_indexNode++;	
		}

		if (Math::distance(m_path[m_path.size() - 1]->position, position) <= 10)
		{
			m_indexNode = 1;
			m_path.clear();
			m_isMoving = false;
			current = target->node;
			return;
		}

		sf::Vector2f dir = m_path[m_indexNode]->position - position;
		position += Math::normalize(dir) * dt * 1000.0f * Settings::speed;
	}
}