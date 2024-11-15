#include <iostream>

#include "Sandbox.hpp"
#include "../Settings.hpp"
#include "../Simulation/Math.hpp"

Sandbox::Sandbox(sf::RenderWindow* window)
{
	p_window = window;
	m_backgroundTex.loadFromFile("../assets/img.jpg");
	m_background.setTexture(m_backgroundTex);
	m_camera = Camera(window);
}

void Sandbox::handleSettings()
{
	ImGui::SliderFloat("Sensitivity", &Settings::sensitivity, 0.1f, 100.0f);
}

void Sandbox::update(float dt)
{
	if (!ImGui::GetIO().WantCaptureMouse)
	{
		m_camera.move();
	}
	

	
}

void Sandbox::render()
{
	p_window->setView(m_camera.view);
	p_window->draw(m_background);
}