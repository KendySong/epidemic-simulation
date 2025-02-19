#include <math.h>

#include "Math.hpp"
#include "Human.hpp"
#include "Building.hpp"
#include <iostream>

Human::Human(Building* home)
{
	this->home = home;
	this->position = home->position;
	this->health = Math::random(80, 101);
	body = sf::CircleShape(5);
	body.setPointCount(3);
	body.setFillColor(sf::Color::Green);
	
	int hourToSleep = Math::random(22, 24);
	int hourToWork = Math::random(6, 10);
	int hourToWorkFinish = Math::random(15, 17);

	m_lifeSchedule[std::pair<int, int>(hourToSleep, 0)] = Activities::Sleep;
	m_lifeSchedule[std::pair<int, int>(1, hourToWork)] = Activities::Sleep;
	m_lifeSchedule[std::pair<int, int>(hourToWork + 1, hourToWorkFinish)] = Activities::Work;
	m_lifeSchedule[std::pair<int, int>(hourToWorkFinish + 1, hourToWorkFinish + 2)] = Activities::Home;
	m_lifeSchedule[std::pair<int, int>(hourToWorkFinish + 3, hourToSleep - 1)] = Math::random(0, 3) == 0 ? Activities::Home : Activities::Entertainment;
}

void Human::draw(sf::RenderTarget& renderTarget)
{
	if (position != home->position)
	{
		body.setPosition(position - sf::Vector2f(body.getRadius(), body.getRadius()));
		renderTarget.draw(body);
	}
}

void Human::update(int hourInDay)
{
	//trouver l'activite, si il n'y est pas y aller

	
	//Segmenter sa journee sur des heures dans plus ou moins les memes plage mais de maniere aleatoire
		//Nuit dodo
		//Matin travail
		//Midi certains vont entertainment mais plus de chance d'aller au taff
		//Aprem ils rentrents chez eux
		//le soir ils sortents
}