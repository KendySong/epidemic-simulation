#include <iostream>
#include <math.h>

#include "Math.hpp"
#include "Human.hpp"
#include "Building.hpp"
#include "../Settings.hpp"
#include "Pathfinding.hpp"

Human::Human(Building* home)
{
	this->home = home;
	this->current = home;
	this->position = home->position;
	this->health = Math::random(80, 101);
	body = sf::CircleShape(5);
	body.setPointCount(3);
	body.setFillColor(sf::Color::Green);
	
	int hourToSleep = Math::random(22, 24);
	int hourToWork = Math::random(6, 10);
	int hourToWorkFinish = Math::random(15, 17);

	lifeSchedule[std::pair<int, int>(hourToSleep, 24)] = Activities::Sleep;
	lifeSchedule[std::pair<int, int>(0, hourToWork)] = Activities::Sleep;
	lifeSchedule[std::pair<int, int>(hourToWork + 1, hourToWorkFinish)] = Activities::Work;
	lifeSchedule[std::pair<int, int>(hourToWorkFinish + 1, hourToWorkFinish + 2)] = Activities::Home;
	lifeSchedule[std::pair<int, int>(hourToWorkFinish + 3, hourToSleep - 1)] = Math::random(0, Settings::stayAtHomeProb) == 0 ? Activities::Home : Activities::Entertainment;

	m_isMoving = false;
	m_indexNode = 1;		//Start from 1 for avoid repeatly going on starting node
}

void Human::draw(sf::RenderTarget& renderTarget)
{
	body.setPosition(position - sf::Vector2f(body.getRadius(), body.getRadius()));
	renderTarget.draw(body);

	/*
	if (Math::distance(position, home->node->position) > 0.01 || Math::distance(position, work->node->position) > 0.01)
	{
		body.setPosition(position - sf::Vector2f(body.getRadius(), body.getRadius()));
		renderTarget.draw(body);
	}
	*/
}

Activities Human::findCurrentAction(int hourInDay)
{
	for (const auto& item : lifeSchedule)
	{
		if (hourInDay >= item.first.first && hourInDay <= item.first.second)
		{
			return item.second;
			break;
		}
	}
	return Activities::Undefined;
}

void Human::update(int hourInDay, float dt)
{
	
	switch (findCurrentAction(hourInDay))
	{
	case Activities::Sleep:
		
		break;

	case Activities::Home:

		break;

	case Activities::Work:
		if (current != work && !m_isMoving)
		{
			m_path = Pathfinding::path(current->node, work->node);
			m_isMoving = true;
		}
		
		if (m_isMoving && m_path.size() > 0)
		{
			sf::Vector2f dir = m_path[m_indexNode]->position - position;
			position += Math::normalize(dir) * dt * 2000.0f * Settings::speed;

			if (Math::distance(m_path[m_indexNode]->position, position) <= 0.001)
			{
				m_indexNode++;
			}

			if (Math::distance(m_path[m_path.size()-1]->position, position) <= 0.01)
			{
				m_indexNode = 1;
				m_path.clear();
				m_isMoving = false;
				current = work;
			}
		}
		

		//If not at workplace
			//Go 
		break;

	case Activities::Entertainment:

		break;
	}
}