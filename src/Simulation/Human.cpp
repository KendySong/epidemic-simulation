#include <iostream>
#include <math.h>

#include "Math.hpp"
#include "Human.hpp"
#include "Building.hpp"
#include "../Settings.hpp"
#include "Pathfinding.hpp"

Human::Human(Building* home, std::vector<Building*>* entertainments)
{
	this->home = home;
	this->current = home;
	this->position = home->position;
	speed = Math::random(Settings::avgHumanSpeed - Settings::avgHumanSpeed/10, Settings::avgHumanSpeed + Settings::avgHumanSpeed/10);
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
	this->entertainments = entertainments;
	m_lastHour = 0;
}

void Human::draw(sf::RenderTarget& renderTarget)
{
	if (Math::distance(position, current->node->position) <= 10)
	{
		return;
	}

	body.setPosition(position - sf::Vector2f(body.getRadius(), body.getRadius()));
	renderTarget.draw(body);
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
		moveToTarget(home, dt);
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
}

void Human::moveToTarget(Building* target, float dt)
{
	if (current != target && !m_isMoving)
	{
		m_path = Pathfinding::path(current->node, target->node);
		m_isMoving = true;
	}

	if (m_isMoving && m_path.size() > 0)
	{
		if (Math::distance(m_path[m_indexNode]->position, position) <= 0.1)
		{
			m_indexNode++;
		}

		if (Math::distance(m_path[m_path.size() - 1]->position, position) <= 0.1)
		{
			m_indexNode = 1;
			m_path.clear();
			m_isMoving = false;
			current = target;
		}

		sf::Vector2f dir = m_path[m_indexNode]->position - position;
		position += Math::normalize(dir) * dt * 2000.0f * Settings::speed;
	}
}