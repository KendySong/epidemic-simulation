#include "Camera.hpp"
#include "../Simulation/Math.hpp"
#include "../Settings.hpp"

Camera::Camera(sf::RenderWindow* window)
{
	m_isMoving = false;
	p_window = window;
	m_zoomFactor = 0;
	view = sf::View(Settings::screen_size / 2.0f, Settings::screen_size);
}

void Camera::move()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = Math::toVec2f(sf::Mouse::getPosition(*p_window));
		m_lastMouseP = !m_isMoving ? mousePos : m_lastMouseP;

		//Apply movement
		sf::Vector2f offset = (m_lastMouseP - mousePos) * Settings::sensitivity;
		view.move(offset);

		m_lastMouseP = mousePos;
		m_isMoving = true;		
	}
	else
	{
		m_isMoving = false;
	}	
}

void Camera::zoom(sf::Event& event)
{
	m_zoomFactor = 1 - event.mouseWheel.delta * 0.1;
	Settings::zoom *= m_zoomFactor;
	Settings::sensitivity = Settings::base_zoom * Settings::zoom;
	view.zoom(m_zoomFactor);
}