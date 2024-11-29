#pragma once
#include <SFML/Graphics.hpp>

class Camera
{
public :
	Camera() = default;
	Camera(sf::RenderWindow* p_window);
	void move();
	void zoom(sf::Event& event);

	sf::View view;

private :
	bool m_isMoving;
	float m_zoomFactor;
	sf::Vector2f m_lastMouseP;
	sf::RenderWindow* p_window;
};