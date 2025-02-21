#pragma once
#include <vector>

#include <SFML/Graphics.hpp>

#include <ImGui/imgui.h>
#include <ImGui/imgui-SFML.h>

#include "Camera.hpp"
#include "../Simulation/City.hpp"

class Sandbox
{
public :
	Sandbox(sf::RenderWindow* window);
	void handleSettings();
	void update(float dt);
	void render();

	Camera camera;

private :
	void getPopulationSample();

	sf::RenderWindow* p_window;

	sf::Sprite m_background;
	sf::Texture m_backgroundTex;

	//Simulation
	sf::RectangleShape m_terrain;
	float m_time;
	int m_hourInDay;
	bool m_pause;
	City m_city;	
	float m_temp;
	int m_day;
	int m_lastHour;
	bool m_everyoneWashHand;
	bool m_everyoneWearMask;
	
	//Gui
	bool m_drawGrid;
	std::vector<bool> m_drawStateRoad;

	//Debug
	bool m_displayHeatMap;
	bool m_displayIntersection;
	bool m_displayMarker;
	Node* m_currentNode;
	sf::CircleShape m_currentNodeMarker;
	std::vector<Node*> m_path;
	std::vector<Human*> m_sample;
};