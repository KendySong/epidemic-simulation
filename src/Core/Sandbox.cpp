#include <iostream>

#include "Sandbox.hpp"
#include "../Settings.hpp"
#include "../Simulation/Math.hpp"

Sandbox::Sandbox(sf::RenderWindow* window)
{
	p_window = window;
	//m_backgroundTex.loadFromFile("../assets/img.jpg");
	//m_background.setTexture(m_backgroundTex);
	camera = Camera(window);
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
	//p_window->draw(m_background);

	for (size_t i = 0; i < m_city.building.size(); i++)
	{
		p_window->draw(m_city.building[i].rect);
	}
}