#include <iostream>

#include "Sandbox.hpp"
#include "../Settings.hpp"
#include "../Simulation/Math.hpp"

Sandbox::Sandbox(sf::RenderWindow* window)
{
	p_window = window;
	m_backgroundTex.loadFromFile("../assets/img.jpg");
	m_background.setTexture(m_backgroundTex);
	camera = Camera(window);

	for (size_t i = 0; i < 5; i++)
	{
		sf::RectangleShape rect(sf::Vector2f(50, 50));
		rect.setPosition(60 * i, 360);
		m_drawables.emplace_back(rect);
	}
}

void Sandbox::handleSettings()
{
	
}

void Sandbox::update(float dt)
{
	if (!ImGui::GetIO().WantCaptureMouse)
	{
		camera.move();
	}	
}

void Sandbox::render()
{
	p_window->setView(camera.view);
	p_window->draw(m_background);

	for (size_t i = 0; i < 5; i++)
	{
		p_window->draw(m_drawables[i]);
	}
}