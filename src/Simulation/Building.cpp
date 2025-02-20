#include <iostream>

#include "Math.hpp"
#include "Building.hpp"
#include "../Settings.hpp"
#include "../Core/Texture.hpp"

Building::Building(sf::Vector2f position)
{
	this->node		= nullptr;
	this->position  = position;

	sf::Vector2f homeSize = sf::Vector2f(Settings::home_size, Settings::home_size);
	rect = sf::RectangleShape(homeSize);
	rect.setPosition(position - homeSize*0.5f);
	rect.setFillColor(sf::Color::White);
	color = sf::Color(Math::random(0, 255), Math::random(0, 255), Math::random(0, 255));
}

void Building::setType(Type type)
{
	this->type = type;
	switch (type)
	{
	case Type::Home:
		rect.setTexture(Texture::instance()->home);
		break;
	case Type::Entertainment:
		rect.setTexture(Texture::instance()->entertainment);
		break;
	case Type::Work:
		rect.setTexture(Texture::instance()->work);
		break;
	}
	
}