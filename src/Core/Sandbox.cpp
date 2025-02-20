#include <iostream>

#include "Sandbox.hpp"
#include "../Settings.hpp"
#include "../Simulation/Math.hpp"
#include "../Simulation/Pathfinding.hpp"

Sandbox::Sandbox(sf::RenderWindow* window)
{
	p_window = window;
	camera = Camera(window);
	m_drawGrid = false;
	m_displayMarker = false;
	m_displayIntersection = false;
	m_time = 0;

	m_drawStateRoad = std::vector<bool>(m_city.roads.size(), true);
	m_terrain = sf::RectangleShape(Settings::screen_size * 1.25f);
	m_terrain.setFillColor(sf::Color(60, 60, 60));
	m_terrain.setPosition(m_terrain.getPosition() - (m_terrain.getSize() - Settings::screen_size) /2.0f);

	//Debug
	m_path = Pathfinding::path(m_city.building[0].node, m_city.building[m_city.building.size() - 1].node);
	m_currentNode = m_city.building[0].node;
	m_currentNodeMarker = sf::CircleShape(10);
	m_currentNodeMarker.setFillColor(sf::Color::Blue);
	m_pause = false;
}

void Sandbox::handleSettings()
{
	ImGui::SeparatorText("City information");

	ImGui::TextColored(ImVec4(0, 1, 0, 1), "Total population :		%i", m_city.humans.size());
	ImGui::Text("Number of home :		  %i", m_city.homeRepartition);
	ImGui::Text("Number of work :		  %i", m_city.workRepartition);
	ImGui::Text("Number of entertainment : %i", m_city.entertainmentRepartition);

	if (ImGui::TreeNode("Population info"))
	{
		for (size_t i = 0; i < Settings::human_per_home/2; i++)
		{
			std::string humanLabel = "Human [" + std::to_string(i) + "]";

			ImGui::SetNextItemWidth(200);
			ImGui::InputFloat2(std::string(humanLabel + " Position").c_str(), &m_city.humans[i].position.x);

			//Display their schedule life
			if (ImGui::TreeNode(humanLabel.c_str()))
			{
				for (const auto& item : m_city.humans[i].lifeSchedule)
				{
					ImGui::Text("from %ih00 to %ih00 : %s", item.first.first, item.first.second == 24 ? 0 : item.first.second, getString(item.second));
				}

				ImGui::TreePop();
			}
			else
			{
				ImGui::SameLine();
				ImGui::TextUnformatted(getString(m_city.humans[i].findCurrentAction(m_hourInDay)).c_str());
			}
		}

		ImGui::TreePop();
	}

	ImGui::Separator();
	if (ImGui::TreeNodeEx("Simulation", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::SeparatorText("Miscellaneous");
			ImGui::TextColored(ImVec4(0, 1, 0, 1), "Hour : %ih00", m_hourInDay);
			ImGui::SetNextItemWidth(200);
			ImGui::DragFloat("Simulation speed", &Settings::speed, 0.1, 0.0, 90);
			ImGui::Checkbox("Pause", &m_pause);

		ImGui::SeparatorText("Temp");
			ImGui::SetNextItemWidth(200);
			ImGui::DragFloat("Max temp", &Settings::tempMax, 0.5);
			ImGui::SetNextItemWidth(200);
			ImGui::DragFloat("Min temp", &Settings::tempMin, 0.5);

			ImGui::Dummy(ImVec2(0.0, 10.0));
			ImGui::TextColored(ImVec4(0, 1, 0, 1), "Temp in C : %f", m_temp);

			static std::vector<float> tempRecords;
			if (!m_pause)
			{
				tempRecords.push_back(m_temp);
			}
		
			if (tempRecords.size() > 5000)
			{
				tempRecords.erase(tempRecords.begin());
			}	

			ImGui::PlotHistogram("",
				tempRecords.data(),
				static_cast<int>(tempRecords.size()),
				0,
				"Temp in C",
				Settings::tempMin * 1.25,
				Settings::tempMax * 1.25,
				ImVec2(300, 150));
		ImGui::TreePop();
	}

	ImGui::Separator();
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

			if (ImGui::TreeNodeEx("Path from first node to last"))
			{
				for (size_t i = 0; i < m_path.size(); i++)
				{
					ImGui::Text("[%f] [%f]", m_path[i]->position.x, m_path[i]->position.y);
				}
				ImGui::TreePop();
			}	

			ImGui::TreePop();
		}

		ImGui::TreePop();
	}
}

void Sandbox::update(float dt)
{
	if (m_displayMarker)
	{
		m_currentNodeMarker.setPosition(
			m_currentNode->position - sf::Vector2f(m_currentNodeMarker.getRadius(), m_currentNodeMarker.getRadius())
		);
	}

	if (!m_pause)
	{
		m_time += dt * Settings::speed;
		m_hourInDay = (int)m_time % 24;
		m_temp = Math::getTemp((m_time / 720) * Settings::speed);
		if (!ImGui::GetIO().WantCaptureMouse)
		{
			camera.move();
		}	

		for (size_t i = 0; i < m_city.humans.size(); i++)
		{
			m_city.humans[i].update(m_hourInDay, dt);
		}
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

	p_window->draw(m_city.roadVertices);
	for (size_t i = 0; i < m_city.building.size(); i++)
	{
		p_window->draw(m_city.building[i].rect);
	}

	for (size_t i = 0; i < m_city.humans.size(); i++)
	{
		m_city.humans[i].draw(*p_window);
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