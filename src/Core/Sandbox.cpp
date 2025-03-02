#include <algorithm>
#include <iostream>
#include <random>

#include "Sandbox.hpp"
#include "../Settings.hpp"
#include "../Simulation/Math.hpp"
#include "../Simulation/Pathfinding.hpp"

Sandbox::Sandbox(sf::RenderWindow* window)
{
	p_window = window;
	camera = Camera(window);
	m_displayIntersection = false;
	m_displayHeatMap = false;
	m_displayMarker = false;
	m_drawGrid = false;
	m_time = 0;
	m_day = 0;

	m_drawStateRoad = std::vector<bool>(m_city.roads.size(), true);
	m_terrain = sf::RectangleShape(Settings::screen_size * 1.25f);
	m_terrain.setFillColor(sf::Color(60, 60, 60));
	m_terrain.setPosition(m_terrain.getPosition() - (m_terrain.getSize() - Settings::screen_size) /2.0f);

	//Debug
	m_path = Pathfinding::path(m_city.building[0].node, m_city.building[m_city.building.size() - 1].node);
	m_currentNode = m_city.building[0].node;
	m_currentNodeMarker = sf::CircleShape(10);
	m_currentNodeMarker.setFillColor(sf::Color::Blue);
	m_nearCircle = sf::CircleShape(Settings::nearDistanceHuman);
	m_nearCircle.setFillColor(sf::Color::Yellow);
	m_nearCircle.setPosition(sf::Vector2f(-500, 500));
	m_pause = false;

	this->getPopulationSample();
	m_basePopulation = m_city.humans.size();
}

void Sandbox::handleSettings()
{
	ImGui::SeparatorText("City information");

	ImGui::TextColored(ImVec4(0, 1, 0, 1),   "Total population  :		%i", m_city.humans.size() - m_city.deadPopulation);
	ImGui::TextColored(ImVec4(1, 0.5, 0, 1), "Total infected    :		%i", m_city.infectedPopulation);
	ImGui::TextColored(ImVec4(1, 0, 0, 1),   "Total dead		:		%i", m_city.deadPopulation);
	ImGui::Spacing();

	if (ImGui::TreeNodeEx("Graph"))
	{
		static std::vector<float> values = { 0.2f, 0.8f, 0.6f, 0.3f, 0.9f, 1.0f, 0.5f, 0.7f, 0.4f, 0.6f };
		ImGui::PlotHistogram("Valeurs", values.data(), values.size(), 0, nullptr, 0.0f, 1.0f, ImVec2(0, 100));

		ImGui::TreePop();
	}

	ImGui::Spacing();
	ImGui::Text("Number of home :		  %i", m_city.homeRepartition);
	ImGui::Text("Number of work :		  %i", m_city.workRepartition);
	ImGui::Text("Number of entertainment : %i", m_city.entertainmentRepartition);

	ImGui::Spacing();
	if (ImGui::TreeNode("Population info"))
	{
		for (size_t i = 0; i < m_sample.size(); i++)
		{
			std::string index = std::to_string(i);
			std::string humanLabel = "Human [" + index + "] [" + getString(m_sample[i]->findCurrentAction(m_hourInDay)) + "]";

			//Display their schedule life
			if (i == 0)
			{
				if (ImGui::TreeNode(humanLabel.c_str()))
				{
					for (const auto& item : m_city.humans[i].lifeSchedule)
					{
						ImGui::Text("from %ih00 to %ih00 : %s", item.first.first, item.first.second == 24 ? 0 : item.first.second, getString(item.second));
					}

					ImGui::TreePop();
				}
			}

			switch (m_sample[i]->status)
			{
			case Status::Alive:
				ImGui::TextColored(ImVec4(0, 1, 0, 1), "State : Alive");
				break;

			case Status::Infected:
				ImGui::TextColored(ImVec4(1, 0.5, 0, 1), "State : Infected");
				break;

			case Status::Dead:
				ImGui::TextColored(ImVec4(1, 0, 0, 1), "State : Dead");
				break;
			}
			
			this->healthBar(m_sample[i]->health, Settings::max_health, ImVec4(0, 1, 0, 1));
			ImGui::SameLine();
			ImGui::Text("HP : [%i/%i]", (int)m_sample[i]->health, Settings::max_health);

			if (m_sample[i]->status == Status::Infected)
			{

				this->healthBar(m_sample[i]->diseaseHp, Settings::base_disease_hp, ImVec4(0, 1, 0, 1));
				ImGui::SameLine();
				ImGui::Text("Disease HP : [%i/%i]", m_sample[i]->diseaseHp, Settings::base_disease_hp);

			}

			ImGui::Text("Age					  : %i", m_sample[i]->age);
			ImGui::Text("Time near infected human : %f", m_sample[i]->riskHumanTimer);
			ImGui::Text("Time in infected zone    : %f", m_sample[i]->riskZoneTimer);
			ImGui::Text("Infectiousness		   : %f", m_sample[i]->infectiousness);
			ImGui::Text("Immunitary system	    : %f", m_sample[i]->immunitaryLevel);
			ImGui::Text("Position			     : [%f] [%f]", m_sample[i]->position.x, m_sample[i]->position.y);
			ImGui::Text("Speed				    : %f", m_sample[i]->speed);
			ImGui::Separator();
		}

		ImGui::TreePop();
	}
	ImGui::Spacing();

	ImGui::Separator();
	if (ImGui::TreeNodeEx("Simulation", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::SeparatorText("Time");
			ImGui::TextColored(ImVec4(0, 1, 0, 1), "Hour : %ih00", m_hourInDay);
			ImGui::Text("Day : %i", m_day);
			ImGui::SetNextItemWidth(200);
			ImGui::DragFloat("Simulation speed", &Settings::speed, 0.1, 0.0, 90);
			ImGui::Checkbox("Pause", &m_pause);
			ImGui::SetNextItemWidth(200);
			if (ImGui::Button("Slow up simulation"))
			{
				Settings::speed = 0.05;
			}

		ImGui::SeparatorText("Disease");
			ImGui::SetNextItemWidth(200);
			ImGui::DragFloat("Mortality", &Settings::mortality, 0.5, 0.0, 500);
			ImGui::SetNextItemWidth(200);
			ImGui::DragFloat("Infectiousness", &Settings::infectiousness, 0.5, 0.0, 5);
			ImGui::SetNextItemWidth(200);
			ImGui::DragFloat("Inverse infectiousness", &Settings::aInfectiousness, 0.5, 0.0, 500);	
			ImGui::SetNextItemWidth(200);
			ImGui::DragFloat("Human near ray", &Settings::nearDistanceHuman, 0.1, 0.0, 100);
			ImGui::Spacing();

			ImGui::Checkbox("Display heatmap", &m_displayHeatMap);
			ImGui::Checkbox("Everyone wash hand", &Settings::everyoneWashHand);
			ImGui::Checkbox("Everyone wear mask", &Settings::everyoneWearMask);
			
		ImGui::SeparatorText("Temp");
			ImGui::SetNextItemWidth(200);
			ImGui::DragFloat("Max temp", &Settings::tempMax, 0.5);
			ImGui::SetNextItemWidth(200);
			ImGui::DragFloat("Min temp", &Settings::tempMin, 0.5);

			ImGui::Dummy(ImVec2(0.0, 10.0));
			ImGui::TextColored(ImVec4(0, 1, 0, 1), "Temp in C : %f", Settings::temp);

			static std::vector<float> tempRecords;
			if (!m_pause)
			{
				tempRecords.push_back(Settings::temp);
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
	if (!ImGui::GetIO().WantCaptureMouse)
	{
		camera.move();
	}

	if (m_displayMarker)
	{
		m_currentNodeMarker.setPosition(
			m_currentNode->position - sf::Vector2f(m_currentNodeMarker.getRadius(), m_currentNodeMarker.getRadius())
		);
		m_nearCircle.setRadius(Settings::nearDistanceHuman);
		
	}

	if (!m_pause)
	{
		m_time += dt * Settings::speed;
		m_hourInDay = ((int)m_time + Settings::start_time) % 24;
		Settings::temp = Math::getTemp((m_time / 720) * Settings::speed);

		if (m_hourInDay == 0 && m_lastHour != m_hourInDay)
		{
			m_day++;
		} 

		for (size_t i = 0; i < m_city.humans.size(); i++)
		{
			if (m_city.humans[i].status != Status::Dead)
			{
				m_city.humans[i].update(m_hourInDay, dt);
			}		
		}

		m_city.updateHeatMap();
		m_lastHour = m_hourInDay;
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
		if (m_city.humans[i].status != Status::Dead)
		{
			m_city.humans[i].draw(*p_window);
		}	
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
		p_window->draw(m_nearCircle);
	}

	if (m_displayHeatMap)
	{
		for (size_t i = 0; i < m_city.heatMapColor.size(); i++)
		{
			p_window->draw(m_city.heatMapColor[i]);
		}
	}
}

void Sandbox::getPopulationSample()
{
	std::vector<int> humansID;
	std::random_device random;
	std::mt19937 s(random());

	for (size_t i = 0; i < m_city.humans.size(); i++)
	{
		humansID.push_back(i);
	}

	std::shuffle(humansID.begin(), humansID.end(), s);
	
	for (size_t i = 0; i < humansID.size(); i++)
	{
		if (m_city.humans[humansID[i]].status != Status::Infected)
		{
			m_sample.push_back(&m_city.humans[humansID[i]]);
			break;
		}
	}

	for (size_t i = 0; i < humansID.size(); i++)
	{
		if (m_city.humans[humansID[i]].status == Status::Infected)
		{
			m_sample.push_back(&m_city.humans[humansID[i]]);
			break;
		}
	}
}

void Sandbox::healthBar(float current, float max, ImVec4 color)
{
	static ImVec2 size = ImVec2(200.0f, 20.0f);
	float progress = current / max;
	ImGui::PushStyleColor(ImGuiCol_PlotHistogram, progress >= 0.5 ? ImVec4(0, 1, 0, 1) : ImVec4(1, 0.5, 0, 1));
	ImGui::ProgressBar(progress, size, "");
	ImGui::PopStyleColor();
}
