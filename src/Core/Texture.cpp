#include "Texture.hpp"

Texture* Texture::s_instance = nullptr;

Texture::Texture()
{
	home = new sf::Texture();
	home->loadFromFile("../assets/home.png");

	work = new sf::Texture();
	work->loadFromFile("../assets/work.png");

	entertainment = new sf::Texture();
	entertainment->loadFromFile("../assets/entertainment.png");
}

Texture* Texture::instance()
{
	if (s_instance == nullptr)
	{
		s_instance = new Texture();
	}
	return s_instance;
}