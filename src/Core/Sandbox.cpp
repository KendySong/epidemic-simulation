#include <iostream>

#include "Sandbox.hpp"
#include "../Settings.hpp"
#include "../Simulation/Math.hpp"

Sandbox::Sandbox(sf::RenderWindow* window)
{
	p_window = window;
	camera = Camera(window);
	m_drawGrid = false;
	m_displayMarker = false;
	m_displayIntersection = false;

	m_drawStateRoad = std::vector<bool>(m_city.roads.size(), true);
	m_terrain = sf::RectangleShape(Settings::screen_size * 1.25f);
	m_terrain.setFillColor(sf::Color(60, 60, 60));
	m_terrain.setPosition(m_terrain.getPosition() - (m_terrain.getSize() - Settings::screen_size) /2.0f);

	//Debug
	m_currentNode = m_city.building[0].node;
	m_currentNodeMarker = sf::CircleShape(10);
	m_currentNodeMarker.setFillColor(sf::Color::Green);
}

void Sandbox::handleSettings()
{
	if (ImGui::TreeNodeEx("Simulation Data"))
	{
		static std::vector<float> tempRecords;
		tempRecords.push_back(m_temp);
		if (tempRecords.size() > 9999)
		{
			tempRecords.erase(tempRecords.begin());
		}

		ImGui::Text("Elapsed Time : %f", m_clTime.getElapsedTime().asSeconds());
		ImGui::Text("Temp in C : %f", m_temp);
		ImGui::PlotHistogram("",
			tempRecords.data(),
			static_cast<int>(tempRecords.size()),
			0,
			"Temp in C",
			Settings::tempMin * 1.25,
			Settings::tempMax * 1.25,
			ImVec2(350, 150));
		ImGui::TreePop();
	}
	if (ImGui::TreeNodeEx("Miscellaneous [Debug]"))
	{	
		ImGui::Text("Mouse position : [%i] [%i]", sf::Mouse::getPosition(*p_window).x, sf::Mouse::getPosition(*p_window).y);
		ImGui::Checkbox("Draw grid", &m_drawGrid);	
		if (ImGui::TreeNodeEx("Intersections"))
		{
			ImGui::Checkbox("Display intersections", &m_displayIntersection);
			ImGui::Text("Number of intersection : %i", m_city.intersections.size());
			for (size_t i = 0; i < m_city.intersections.size(); i++)
			{
				ImGui::Text("Position : [%f] [%f]", m_city.intersections[i].getPosition().x, m_city.intersections[i].getPosition().y);
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNodeEx("Graph"))
		{
			ImGui::Checkbox("Display marker", &m_displayMarker);

			static int currentI = 0;
			std::string currentS = "[" + std::to_string(m_currentNode->position.x) + "] [" + std::to_string(m_currentNode->position.y) + "]";
			const char* previewValue = "";
			ImGui::Text("Current node : [%f][%f]", m_currentNode->position.x, m_currentNode->position.y);
			if (ImGui::BeginCombo(" ", currentS.c_str()))
			{
				for (int i = 0; i < m_currentNode->links.size(); i++)
				{
					bool selected = (currentI == i);
					std::string itemS = "[" + std::to_string(m_currentNode->links[i]->position.x) + "] [" + std::to_string(m_currentNode->links[i]->position.y) + "]";
					if (ImGui::Selectable(itemS.c_str(), selected))
					{
						currentI = i;
						m_currentNode = m_currentNode->links[i];
					}

					if (selected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}

			ImGui::TreePop();
		}
		ImGui::TreePop();
	}

}

void Sandbox::update(float dt)
{
	m_temp = Math::getTemp(m_clTime.getElapsedTime().asSeconds());
	if (!ImGui::GetIO().WantCaptureMouse)
	{
		camera.move();
	}

	if (m_displayMarker)
	{
		m_currentNodeMarker.setPosition(m_currentNode->position);
	}	
}

void Sandbox::render()
{
	p_window->setView(camera.view);
	p_window->draw(m_terrain);

	if (m_drawGrid)
	{
		p_window->draw(m_city.gridLines);
	}

	for (size_t i = 0; i < m_city.roads.size(); i++)
	{
		if (m_drawStateRoad[i])
		{
			p_window->draw(m_city.roads[i].lines);
		}	
	}

	for (size_t i = 0; i < m_city.building.size(); i++)
	{
		p_window->draw(m_city.building[i].rect);
	}

	if (m_displayIntersection)
	{
		for (size_t i = 0; i < m_city.intersections.size(); i++)
		{
			p_window->draw(m_city.intersections[i]);
		}
	}
	
	if (m_displayMarker)
	{
		p_window->draw(m_currentNodeMarker);
	}
}