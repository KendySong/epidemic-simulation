#pragma once
#include <SFML/Graphics.hpp>

class Camera
{
public :
	Camera() = default;
	Camera(sf::RenderWindow* p_window);
	void move();

	sf::View view;

private :
	bool m_isMoving;
	sf::Vector2f m_lastMouseP;
	sf::RenderWindow* p_window;
};