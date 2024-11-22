#include <iostream>

#include "Sandbox.hpp"
#include "../Settings.hpp"
#include "../Simulation/Math.hpp"

Sandbox::Sandbox(sf::RenderWindow* window)
{
	p_window = window;
	m_backgroundTex.loadFromFile("../assets/map-1.png");
	m_background.setTexture(m_backgroundTex);
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
	p_window->draw(m_background);
}