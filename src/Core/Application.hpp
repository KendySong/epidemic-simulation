#pragma once
#include <SFML/Graphics.hpp>

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
};