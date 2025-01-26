#include <iostream>

#include "Sandbox.hpp"
#include "../Settings.hpp"
#include "../Simulation/Math.hpp"

Sandbox::Sandbox(sf::RenderWindow* window)
{
	p_window = window;
	camera = Camera(window);
	m_drawGrid = false;

	m_drawStateRoad = std::vector<bool>(m_city.roads.size(), true);
}

void Sandbox::handleSettings()
{
	static std::vector<float> tempRecords;
	tempRecords.push_back(m_temp);
	if (tempRecords.size() > 9999)
	{
		tempRecords.erase(tempRecords.begin());
	}



	ImGui::Text("Elapsed Time : %f", (m_clTime.getElapsedTime().asSeconds() * 12) / 24);
	ImGui::Text("Temp in C : %f", m_temp);


	ImGui::PlotLines("",
		tempRecords.data(),
		static_cast<int>(tempRecords.size()),
		0,
		"Temp in C",
		Settings::tempMin * 1.25,
		Settings::tempMax * 1.25,
		ImVec2(350, 150));

	if (ImGui::TreeNodeEx("Miscellaneous [Debug]", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Checkbox("Draw Grid", &m_drawGrid);
		ImGui::Text("Number of intersection : %i", m_city.intersections.size());
		ImGui::Text("Mouse position : [%i] [%i]", sf::Mouse::getPosition(*p_window).x, sf::Mouse::getPosition(*p_window).y);
		if (ImGui::TreeNodeEx("Intersections"))
		{
			for (size_t i = 0; i < m_city.intersections.size(); i++)
			{
				ImGui::Text("Position : [%f] [%f]", m_city.intersections[i].getPosition().x, m_city.intersections[i].getPosition().y);
			}
			ImGui::TreePop();
		}

		ImGui::Text("Number of roads : %i", m_city.roads.size());
		for (size_t i = 0; i < m_drawStateRoad.size(); i++)
		{			
			std::string lblRoad = "Road [" + std::to_string(i) + "]";
			bool currentDraw = m_drawStateRoad[i];
			ImGui::Checkbox(lblRoad.c_str(), &currentDraw);
			m_drawStateRoad[i] = currentDraw;
		}
		ImGui::TreePop();
	}
}

void Sandbox::update(float dt)
{
	m_temp = Math::getTemp(m_clTime.getElapsedTime().asSeconds() * 25);
	if (!ImGui::GetIO().WantCaptureMouse)
	{
		camera.move();
	}
}

void Sandbox::render()
{
	p_window->setView(camera.view);
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
		if (m_drawStateRoad[i])
		{
			p_window->draw(m_city.roads[i]);
		}	
	}

	for (size_t i = 0; i < m_city.intersections.size(); i++)
	{
		p_window->draw(m_city.intersections[i]);
	}
}