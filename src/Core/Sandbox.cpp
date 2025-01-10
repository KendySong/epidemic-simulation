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
	m_drawGrid = false;
}

void Sandbox::handleSettings()
{
	ImGui::Checkbox("Draw Grid", &m_drawGrid);
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
	
	//p_window->draw(m_city.s);
	if (m_drawGrid)
	{
		p_window->draw(m_city.gridLines);
	}

	for (size_t i = 0; i < m_city.building.size(); i++)
	{
		p_window->draw(m_city.building[i].rect);
	}

	for (size_t i = 0; i < m_city.roads.size(); i++)
	{
		p_window->draw(m_city.roads[i]);
	}

	for (size_t i = 0; i < m_city.intersections.size(); i++)
	{
		p_window->draw(m_city.intersections[i]);
	}
}