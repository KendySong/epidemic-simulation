#pragma once
#include <SFML/Graphics.hpp>

#include "Sandbox.hpp"

class Application
{
private:
	Application();

public:
	static Application* instance() noexcept;
	int run();

private:
	static Application* s_app;
	sf::RenderWindow* p_window;
	sf::Clock m_deltaClock;
	sf::Time m_deltaTime;
	sf::Event m_event;

	sf::Clock m_fpsClock;
	int m_fpsDisplay;
	int m_fps;

	Sandbox* p_sandbox;
	float m_zoomFactor;
};