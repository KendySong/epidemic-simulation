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

	if (ImGui::TreeNodeEx("Miscellaneous", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Text("Number of intersection : %i", m_city.intersections.size());
		ImGui::Text("Mouse position : [%i] [%i]", sf::Mouse::getPosition(*p_window).x, sf::Mouse::getPosition(*p_window).y);
		for (size_t i = 0; i < m_city.intersections.size(); i++)
		{
			ImGui::Text("Position : [%f] [%f]", m_city.intersections[i].getPosition().x, m_city.intersections[i].getPosition().y);
		}
		ImGui::Text("Number of roads : %i", m_city.roads.size());
		ImGui::TreePop();
	}
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